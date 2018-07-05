#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                             *
 * Basic functions                                                             *
 *                                                                             *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
FILE *open_file(char *fName, char *mode);

double **malloc_2d_double(int nRow, int nCol);
double **memcpy_2d_double(double **source, int nRow, int nCol);
void free_2d_double(double **p, int nRow);

int bisection_search(double a, double *x, int nX);
double interp(double xp, double *x, double *y, int nPts);
double trapz_table(double *y, double *x, int nPts, double a, double b);
double trapz_filter(double *filter, double *flux, double *waves, int nWaves);

struct linResult {
    double slope;
    double intercept;
    double R;
};
struct linResult linregress(double *x, double *y, int nPts);


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                             *
 * SFHs related                                                                *
 *                                                                             *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
struct ssp {
    short index;
    float metals;
    float sfr;
};
struct csp {
    struct ssp *bursts;
    int nBurst;
};
struct gal_params {
    double z;
    int nAgeStep;
    double *ageStep;
    int nGal;
    int *indices;
    struct csp *histories;
};


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                             *
 * SEDs and dust related                                                       *
 *                                                                             *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
struct sed_params {
    // Raw templates
    int minZ;
    int maxZ;
    int nZ;
    double *Z;
    int nWaves;
    double *waves;
    int nAge;
    double *age;
    double *raw;
    // Redshift
    double z;
    // Filters
    int nFlux;
    int nObs;
    int *nFilterWaves;
    double *filterWaves;
    double *filters;
    double *logWaves;
    // IGM absorption
    double *LyAbsorption;
    // Working templates
    int nAgeStep;
    double *ageStep;
    double *integrated;
    double *ready;
    double *working;
    double *inBC;
    double *outBC;
};

struct dust_params {
    double tauUV_ISM;
    double nISM;
    double tauUV_BC;
    double nBC;
    double tBC;
};

#ifndef _SECTOR_
void init_templates_raw(struct sed_params *spectra, char *fName);
void shrink_templates_raw(struct sed_params *spectra, double maxAge);
double *composite_spectra_cext(struct sed_params *spectra,
                               struct gal_params *galParams, struct dust_params *dustParams,
                               short outType, short nThread);
#endif
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u32 ;
struct MT2063_AvoidSpursData_t {int f_ref; int f_if1_Center; int f_if1_bw; int f_in; int f_LO1_FracN_Avoid; int f_out; int f_LO2_FracN_Avoid; int /*<<< orphan*/  avoidDECT; int /*<<< orphan*/ * freeZones; int /*<<< orphan*/ * usedZones; scalar_t__ nZones; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT2063_AddExclZone (struct MT2063_AvoidSpursData_t*,int,int) ; 
 scalar_t__ MT2063_EXCLUDE_EURO_DECT_FREQUENCIES (int /*<<< orphan*/ ) ; 
 scalar_t__ MT2063_EXCLUDE_US_DECT_FREQUENCIES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintk (int,char*) ; 

__attribute__((used)) static void MT2063_ResetExclZones(struct MT2063_AvoidSpursData_t *pAS_Info)
{
	u32 center;

	dprintk(2, "\n");

	pAS_Info->nZones = 0;	/*  this clears the used list  */
	pAS_Info->usedZones = NULL;	/*  reset ptr                  */
	pAS_Info->freeZones = NULL;	/*  reset ptr                  */

	center =
	    pAS_Info->f_ref *
	    ((pAS_Info->f_if1_Center - pAS_Info->f_if1_bw / 2 +
	      pAS_Info->f_in) / pAS_Info->f_ref) - pAS_Info->f_in;
	while (center <
	       pAS_Info->f_if1_Center + pAS_Info->f_if1_bw / 2 +
	       pAS_Info->f_LO1_FracN_Avoid) {
		/*  Exclude LO1 FracN  */
		MT2063_AddExclZone(pAS_Info,
				   center - pAS_Info->f_LO1_FracN_Avoid,
				   center - 1);
		MT2063_AddExclZone(pAS_Info, center + 1,
				   center + pAS_Info->f_LO1_FracN_Avoid);
		center += pAS_Info->f_ref;
	}

	center =
	    pAS_Info->f_ref *
	    ((pAS_Info->f_if1_Center - pAS_Info->f_if1_bw / 2 -
	      pAS_Info->f_out) / pAS_Info->f_ref) + pAS_Info->f_out;
	while (center <
	       pAS_Info->f_if1_Center + pAS_Info->f_if1_bw / 2 +
	       pAS_Info->f_LO2_FracN_Avoid) {
		/*  Exclude LO2 FracN  */
		MT2063_AddExclZone(pAS_Info,
				   center - pAS_Info->f_LO2_FracN_Avoid,
				   center - 1);
		MT2063_AddExclZone(pAS_Info, center + 1,
				   center + pAS_Info->f_LO2_FracN_Avoid);
		center += pAS_Info->f_ref;
	}

	if (MT2063_EXCLUDE_US_DECT_FREQUENCIES(pAS_Info->avoidDECT)) {
		/*  Exclude LO1 values that conflict with DECT channels */
		MT2063_AddExclZone(pAS_Info, 1920836000 - pAS_Info->f_in, 1922236000 - pAS_Info->f_in);	/* Ctr = 1921.536 */
		MT2063_AddExclZone(pAS_Info, 1922564000 - pAS_Info->f_in, 1923964000 - pAS_Info->f_in);	/* Ctr = 1923.264 */
		MT2063_AddExclZone(pAS_Info, 1924292000 - pAS_Info->f_in, 1925692000 - pAS_Info->f_in);	/* Ctr = 1924.992 */
		MT2063_AddExclZone(pAS_Info, 1926020000 - pAS_Info->f_in, 1927420000 - pAS_Info->f_in);	/* Ctr = 1926.720 */
		MT2063_AddExclZone(pAS_Info, 1927748000 - pAS_Info->f_in, 1929148000 - pAS_Info->f_in);	/* Ctr = 1928.448 */
	}

	if (MT2063_EXCLUDE_EURO_DECT_FREQUENCIES(pAS_Info->avoidDECT)) {
		MT2063_AddExclZone(pAS_Info, 1896644000 - pAS_Info->f_in, 1898044000 - pAS_Info->f_in);	/* Ctr = 1897.344 */
		MT2063_AddExclZone(pAS_Info, 1894916000 - pAS_Info->f_in, 1896316000 - pAS_Info->f_in);	/* Ctr = 1895.616 */
		MT2063_AddExclZone(pAS_Info, 1893188000 - pAS_Info->f_in, 1894588000 - pAS_Info->f_in);	/* Ctr = 1893.888 */
		MT2063_AddExclZone(pAS_Info, 1891460000 - pAS_Info->f_in, 1892860000 - pAS_Info->f_in);	/* Ctr = 1892.16  */
		MT2063_AddExclZone(pAS_Info, 1889732000 - pAS_Info->f_in, 1891132000 - pAS_Info->f_in);	/* Ctr = 1890.432 */
		MT2063_AddExclZone(pAS_Info, 1888004000 - pAS_Info->f_in, 1889404000 - pAS_Info->f_in);	/* Ctr = 1888.704 */
		MT2063_AddExclZone(pAS_Info, 1886276000 - pAS_Info->f_in, 1887676000 - pAS_Info->f_in);	/* Ctr = 1886.976 */
		MT2063_AddExclZone(pAS_Info, 1884548000 - pAS_Info->f_in, 1885948000 - pAS_Info->f_in);	/* Ctr = 1885.248 */
		MT2063_AddExclZone(pAS_Info, 1882820000 - pAS_Info->f_in, 1884220000 - pAS_Info->f_in);	/* Ctr = 1883.52  */
		MT2063_AddExclZone(pAS_Info, 1881092000 - pAS_Info->f_in, 1882492000 - pAS_Info->f_in);	/* Ctr = 1881.792 */
	}
}
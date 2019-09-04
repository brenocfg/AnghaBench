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
struct MT2063_AvoidSpursData_t {int bSpurAvoided; int nSpursFound; scalar_t__ maxH1; int bSpurPresent; int f_LO1; int f_in; int f_LO2; scalar_t__ f_out_bw; scalar_t__ f_if1_bw; int f_if1_Center; } ;

/* Variables and functions */
 void* IsSpurInBand (struct MT2063_AvoidSpursData_t*,int*,int*) ; 
 int /*<<< orphan*/  MT2063_AddExclZone (struct MT2063_AvoidSpursData_t*,int,int) ; 
 int MT2063_ChooseFirstIF (struct MT2063_AvoidSpursData_t*) ; 
 int MT2063_SPUR_CNT_MASK ; 
 int MT2063_SPUR_PRESENT_ERR ; 
 int MT2063_SPUR_SHIFT ; 
 int /*<<< orphan*/  dprintk (int,char*) ; 

__attribute__((used)) static u32 MT2063_AvoidSpurs(struct MT2063_AvoidSpursData_t *pAS_Info)
{
	int status = 0;
	u32 fm, fp;		/*  restricted range on LO's        */
	pAS_Info->bSpurAvoided = 0;
	pAS_Info->nSpursFound = 0;

	dprintk(2, "\n");

	if (pAS_Info->maxH1 == 0)
		return 0;

	/*
	 * Avoid LO Generated Spurs
	 *
	 * Make sure that have no LO-related spurs within the IF output
	 * bandwidth.
	 *
	 * If there is an LO spur in this band, start at the current IF1 frequency
	 * and work out until we find a spur-free frequency or run up against the
	 * 1st IF SAW band edge.  Use temporary copies of fLO1 and fLO2 so that they
	 * will be unchanged if a spur-free setting is not found.
	 */
	pAS_Info->bSpurPresent = IsSpurInBand(pAS_Info, &fm, &fp);
	if (pAS_Info->bSpurPresent) {
		u32 zfIF1 = pAS_Info->f_LO1 - pAS_Info->f_in;	/*  current attempt at a 1st IF  */
		u32 zfLO1 = pAS_Info->f_LO1;	/*  current attempt at an LO1 freq  */
		u32 zfLO2 = pAS_Info->f_LO2;	/*  current attempt at an LO2 freq  */
		u32 delta_IF1;
		u32 new_IF1;

		/*
		 **  Spur was found, attempt to find a spur-free 1st IF
		 */
		do {
			pAS_Info->nSpursFound++;

			/*  Raise f_IF1_upper, if needed  */
			MT2063_AddExclZone(pAS_Info, zfIF1 - fm, zfIF1 + fp);

			/*  Choose next IF1 that is closest to f_IF1_CENTER              */
			new_IF1 = MT2063_ChooseFirstIF(pAS_Info);

			if (new_IF1 > zfIF1) {
				pAS_Info->f_LO1 += (new_IF1 - zfIF1);
				pAS_Info->f_LO2 += (new_IF1 - zfIF1);
			} else {
				pAS_Info->f_LO1 -= (zfIF1 - new_IF1);
				pAS_Info->f_LO2 -= (zfIF1 - new_IF1);
			}
			zfIF1 = new_IF1;

			if (zfIF1 > pAS_Info->f_if1_Center)
				delta_IF1 = zfIF1 - pAS_Info->f_if1_Center;
			else
				delta_IF1 = pAS_Info->f_if1_Center - zfIF1;

			pAS_Info->bSpurPresent = IsSpurInBand(pAS_Info, &fm, &fp);
		/*
		 *  Continue while the new 1st IF is still within the 1st IF bandwidth
		 *  and there is a spur in the band (again)
		 */
		} while ((2 * delta_IF1 + pAS_Info->f_out_bw <= pAS_Info->f_if1_bw) && pAS_Info->bSpurPresent);

		/*
		 * Use the LO-spur free values found.  If the search went all
		 * the way to the 1st IF band edge and always found spurs, just
		 * leave the original choice.  It's as "good" as any other.
		 */
		if (pAS_Info->bSpurPresent == 1) {
			status |= MT2063_SPUR_PRESENT_ERR;
			pAS_Info->f_LO1 = zfLO1;
			pAS_Info->f_LO2 = zfLO2;
		} else
			pAS_Info->bSpurAvoided = 1;
	}

	status |=
	    ((pAS_Info->
	      nSpursFound << MT2063_SPUR_SHIFT) & MT2063_SPUR_CNT_MASK);

	return status;
}
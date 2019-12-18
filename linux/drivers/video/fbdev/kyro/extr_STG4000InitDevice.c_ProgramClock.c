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

/* Variables and functions */
 int STG4K3_PLL_MAXR_VCO ; 
 int STG4K3_PLL_MAX_F ; 
 int STG4K3_PLL_MAX_R ; 
 int STG4K3_PLL_MAX_VCO ; 
 int STG4K3_PLL_MINR_VCO ; 
 int STG4K3_PLL_MIN_F ; 
 int STG4K3_PLL_MIN_R ; 
 int STG4K3_PLL_SCALER ; 

u32 ProgramClock(u32 refClock,
		   u32 coreClock,
		   u32 * FOut, u32 * ROut, u32 * POut)
{
	u32 R = 0, F = 0, OD = 0, ODIndex = 0;
	u32 ulBestR = 0, ulBestF = 0, ulBestOD = 0;
	u32 ulBestVCO = 0, ulBestClk = 0, ulBestScore = 0;
	u32 ulScore, ulPhaseScore, ulVcoScore;
	u32 ulTmp = 0, ulVCO;
	u32 ulScaleClockReq, ulMinClock, ulMaxClock;
	u32 ODValues[] = { 1, 2, 0 };

	/* Translate clock in Hz */
	coreClock *= 100;	/* in Hz */
	refClock *= 1000;	/* in Hz */

	/* Work out acceptable clock
	 * The method calculates ~ +- 0.4% (1/256)
	 */
	ulMinClock = coreClock - (coreClock >> 8);
	ulMaxClock = coreClock + (coreClock >> 8);

	/* Scale clock required for use in calculations */
	ulScaleClockReq = coreClock >> STG4K3_PLL_SCALER;

	/* Iterate through post divider values */
	for (ODIndex = 0; ODIndex < 3; ODIndex++) {
		OD = ODValues[ODIndex];
		R = STG4K3_PLL_MIN_R;

		/* loop for pre-divider from min to max  */
		while (R <= STG4K3_PLL_MAX_R) {
			/* estimate required feedback multiplier */
			ulTmp = R * (ulScaleClockReq << OD);

			/* F = ClkRequired * R * (2^OD) / Fref */
			F = (u32)(ulTmp / (refClock >> STG4K3_PLL_SCALER));

			/* compensate for accuracy */
			if (F > STG4K3_PLL_MIN_F)
				F--;


			/*
			 * We should be close to our target frequency (if it's
			 * achievable with current OD & R) let's iterate
			 * through F for best fit
			 */
			while ((F >= STG4K3_PLL_MIN_F) &&
			       (F <= STG4K3_PLL_MAX_F)) {
				/* Calc VCO at full accuracy */
				ulVCO = refClock / R;
				ulVCO = F * ulVCO;

				/*
				 * Check it's within restricted VCO range
				 * unless of course the desired frequency is
				 * above the restricted range, then test
				 * against VCO limit
				 */
				if ((ulVCO >= STG4K3_PLL_MINR_VCO) &&
				    ((ulVCO <= STG4K3_PLL_MAXR_VCO) ||
				     ((coreClock > STG4K3_PLL_MAXR_VCO)
				      && (ulVCO <= STG4K3_PLL_MAX_VCO)))) {
					ulTmp = (ulVCO >> OD);	/* Clock = VCO / (2^OD) */

					/* Is this clock good enough? */
					if ((ulTmp >= ulMinClock)
					    && (ulTmp <= ulMaxClock)) {
						ulPhaseScore = (((refClock / R) - (refClock / STG4K3_PLL_MAX_R))) / ((refClock - (refClock / STG4K3_PLL_MAX_R)) >> 10);

						ulVcoScore = ((ulVCO - STG4K3_PLL_MINR_VCO)) / ((STG4K3_PLL_MAXR_VCO - STG4K3_PLL_MINR_VCO) >> 10);
						ulScore = ulPhaseScore + ulVcoScore;

						if (!ulBestScore) {
							ulBestVCO = ulVCO;
							ulBestOD = OD;
							ulBestF = F;
							ulBestR = R;
							ulBestClk = ulTmp;
							ulBestScore =
							    ulScore;
						}
						/* is this better, ( aim for highest Score) */
			/*--------------------------------------------------------------------------
                             Here we want to use a scoring system which will take account of both the
                            value at the phase comparater and the VCO output
                             to do this we will use a cumulative score between the two
                          The way this ends up is that we choose the first value in the loop anyway
                          but we shall keep this code in case new restrictions come into play
                          --------------------------------------------------------------------------*/
						if ((ulScore >= ulBestScore) && (OD > 0)) {
							ulBestVCO = ulVCO;
							ulBestOD = OD;
							ulBestF = F;
							ulBestR = R;
							ulBestClk = ulTmp;
							ulBestScore =
							    ulScore;
						}
					}
				}
				F++;
			}
			R++;
		}
	}

	/*
	   did we find anything?
	   Then return RFOD
	 */
	if (ulBestScore) {
		*ROut = ulBestR;
		*FOut = ulBestF;

		if ((ulBestOD == 2) || (ulBestOD == 3)) {
			*POut = 3;
		} else
			*POut = ulBestOD;

	}

	return (ulBestClk);
}
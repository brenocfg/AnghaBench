#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int* cal; int* pwr; } ;
struct TYPE_3__ {int* cal; int* pwr; } ;
struct ath_hw {TYPE_2__ nf_2g; TYPE_1__ nf_5g; } ;
struct ath_common {int dummy; } ;

/* Variables and functions */
 int AR5416_MAX_CHAINS ; 
 int AR9300_MAX_CHAINS ; 
 int AR9300_NUM_2G_CAL_PIERS ; 
 int AR9300_NUM_5G_CAL_PIERS ; 
 int /*<<< orphan*/  EEPROM ; 
 int /*<<< orphan*/  ar9003_hw_cal_pier_get (struct ath_hw*,int,int,int,int*,int*,int*,int*,int*,int*) ; 
 int /*<<< orphan*/  ar9003_hw_power_control_override (struct ath_hw*,int,int*,int*,int*) ; 
 struct ath_common* ath9k_hw_common (struct ath_hw*) ; 
 int /*<<< orphan*/  ath_dbg (struct ath_common*,int /*<<< orphan*/ ,char*,int,int,int,int,...) ; 
 int interpolate (int,int,int,int,int) ; 

__attribute__((used)) static int ar9003_hw_calibration_apply(struct ath_hw *ah, int frequency)
{
	int ichain, ipier, npier;
	int mode;
	int lfrequency[AR9300_MAX_CHAINS],
	    lcorrection[AR9300_MAX_CHAINS],
	    ltemperature[AR9300_MAX_CHAINS], lvoltage[AR9300_MAX_CHAINS],
	    lnf_cal[AR9300_MAX_CHAINS], lnf_pwr[AR9300_MAX_CHAINS];
	int hfrequency[AR9300_MAX_CHAINS],
	    hcorrection[AR9300_MAX_CHAINS],
	    htemperature[AR9300_MAX_CHAINS], hvoltage[AR9300_MAX_CHAINS],
	    hnf_cal[AR9300_MAX_CHAINS], hnf_pwr[AR9300_MAX_CHAINS];
	int fdiff;
	int correction[AR9300_MAX_CHAINS],
	    voltage[AR9300_MAX_CHAINS], temperature[AR9300_MAX_CHAINS],
	    nf_cal[AR9300_MAX_CHAINS], nf_pwr[AR9300_MAX_CHAINS];
	int pfrequency, pcorrection, ptemperature, pvoltage,
	    pnf_cal, pnf_pwr;
	struct ath_common *common = ath9k_hw_common(ah);

	mode = (frequency >= 4000);
	if (mode)
		npier = AR9300_NUM_5G_CAL_PIERS;
	else
		npier = AR9300_NUM_2G_CAL_PIERS;

	for (ichain = 0; ichain < AR9300_MAX_CHAINS; ichain++) {
		lfrequency[ichain] = 0;
		hfrequency[ichain] = 100000;
	}
	/* identify best lower and higher frequency calibration measurement */
	for (ichain = 0; ichain < AR9300_MAX_CHAINS; ichain++) {
		for (ipier = 0; ipier < npier; ipier++) {
			if (!ar9003_hw_cal_pier_get(ah, mode, ipier, ichain,
						    &pfrequency, &pcorrection,
						    &ptemperature, &pvoltage,
						    &pnf_cal, &pnf_pwr)) {
				fdiff = frequency - pfrequency;

				/*
				 * this measurement is higher than
				 * our desired frequency
				 */
				if (fdiff <= 0) {
					if (hfrequency[ichain] <= 0 ||
					    hfrequency[ichain] >= 100000 ||
					    fdiff >
					    (frequency - hfrequency[ichain])) {
						/*
						 * new best higher
						 * frequency measurement
						 */
						hfrequency[ichain] = pfrequency;
						hcorrection[ichain] =
						    pcorrection;
						htemperature[ichain] =
						    ptemperature;
						hvoltage[ichain] = pvoltage;
						hnf_cal[ichain] = pnf_cal;
						hnf_pwr[ichain] = pnf_pwr;
					}
				}
				if (fdiff >= 0) {
					if (lfrequency[ichain] <= 0
					    || fdiff <
					    (frequency - lfrequency[ichain])) {
						/*
						 * new best lower
						 * frequency measurement
						 */
						lfrequency[ichain] = pfrequency;
						lcorrection[ichain] =
						    pcorrection;
						ltemperature[ichain] =
						    ptemperature;
						lvoltage[ichain] = pvoltage;
						lnf_cal[ichain] = pnf_cal;
						lnf_pwr[ichain] = pnf_pwr;
					}
				}
			}
		}
	}

	/* interpolate  */
	for (ichain = 0; ichain < AR9300_MAX_CHAINS; ichain++) {
		ath_dbg(common, EEPROM,
			"ch=%d f=%d low=%d %d h=%d %d n=%d %d p=%d %d\n",
			ichain, frequency, lfrequency[ichain],
			lcorrection[ichain], hfrequency[ichain],
			hcorrection[ichain], lnf_cal[ichain],
			hnf_cal[ichain], lnf_pwr[ichain],
			hnf_pwr[ichain]);
		/* they're the same, so just pick one */
		if (hfrequency[ichain] == lfrequency[ichain]) {
			correction[ichain] = lcorrection[ichain];
			voltage[ichain] = lvoltage[ichain];
			temperature[ichain] = ltemperature[ichain];
			nf_cal[ichain] = lnf_cal[ichain];
			nf_pwr[ichain] = lnf_pwr[ichain];
		}
		/* the low frequency is good */
		else if (frequency - lfrequency[ichain] < 1000) {
			/* so is the high frequency, interpolate */
			if (hfrequency[ichain] - frequency < 1000) {

				correction[ichain] = interpolate(frequency,
						lfrequency[ichain],
						hfrequency[ichain],
						lcorrection[ichain],
						hcorrection[ichain]);

				temperature[ichain] = interpolate(frequency,
						lfrequency[ichain],
						hfrequency[ichain],
						ltemperature[ichain],
						htemperature[ichain]);

				voltage[ichain] = interpolate(frequency,
						lfrequency[ichain],
						hfrequency[ichain],
						lvoltage[ichain],
						hvoltage[ichain]);

				nf_cal[ichain] = interpolate(frequency,
						lfrequency[ichain],
						hfrequency[ichain],
						lnf_cal[ichain],
						hnf_cal[ichain]);

				nf_pwr[ichain] = interpolate(frequency,
						lfrequency[ichain],
						hfrequency[ichain],
						lnf_pwr[ichain],
						hnf_pwr[ichain]);
			}
			/* only low is good, use it */
			else {
				correction[ichain] = lcorrection[ichain];
				temperature[ichain] = ltemperature[ichain];
				voltage[ichain] = lvoltage[ichain];
				nf_cal[ichain] = lnf_cal[ichain];
				nf_pwr[ichain] = lnf_pwr[ichain];
			}
		}
		/* only high is good, use it */
		else if (hfrequency[ichain] - frequency < 1000) {
			correction[ichain] = hcorrection[ichain];
			temperature[ichain] = htemperature[ichain];
			voltage[ichain] = hvoltage[ichain];
			nf_cal[ichain] = hnf_cal[ichain];
			nf_pwr[ichain] = hnf_pwr[ichain];
		} else {	/* nothing is good, presume 0???? */
			correction[ichain] = 0;
			temperature[ichain] = 0;
			voltage[ichain] = 0;
			nf_cal[ichain] = 0;
			nf_pwr[ichain] = 0;
		}
	}

	ar9003_hw_power_control_override(ah, frequency, correction, voltage,
					 temperature);

	ath_dbg(common, EEPROM,
		"for frequency=%d, calibration correction = %d %d %d\n",
		frequency, correction[0], correction[1], correction[2]);

	/* Store calibrated noise floor values */
	for (ichain = 0; ichain < AR5416_MAX_CHAINS; ichain++)
		if (mode) {
			ah->nf_5g.cal[ichain] = nf_cal[ichain];
			ah->nf_5g.pwr[ichain] = nf_pwr[ichain];
		} else {
			ah->nf_2g.cal[ichain] = nf_cal[ichain];
			ah->nf_2g.pwr[ichain] = nf_pwr[ichain];
		}

	return 0;
}
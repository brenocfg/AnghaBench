#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * calData; } ;
struct ath_hw {int /*<<< orphan*/  supp_cals; int /*<<< orphan*/  enabled_cals; TYPE_1__ iq_caldata; } ;

/* Variables and functions */
 scalar_t__ AR_SREV_9300_20_OR_LATER (struct ath_hw*) ; 
 int /*<<< orphan*/  AR_SREV_9340 (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9485_OR_LATER (struct ath_hw*) ; 
 int /*<<< orphan*/  IQ_MISMATCH_CAL ; 
 int /*<<< orphan*/  TX_IQ_CAL ; 
 int /*<<< orphan*/  TX_IQ_ON_AGC_CAL ; 
 int /*<<< orphan*/  iq_cal_single_sample ; 

__attribute__((used)) static void ar9003_hw_init_cal_settings(struct ath_hw *ah)
{
	ah->iq_caldata.calData = &iq_cal_single_sample;

	if (AR_SREV_9300_20_OR_LATER(ah)) {
		ah->enabled_cals |= TX_IQ_CAL;
		if (AR_SREV_9485_OR_LATER(ah) && !AR_SREV_9340(ah))
			ah->enabled_cals |= TX_IQ_ON_AGC_CAL;
	}

	ah->supp_cals = IQ_MISMATCH_CAL;
}
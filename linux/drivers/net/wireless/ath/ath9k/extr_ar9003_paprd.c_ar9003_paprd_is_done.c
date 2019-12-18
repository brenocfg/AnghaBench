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
struct ath_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR_PHY_PAPRD_TRAINER_STAT1 ; 
 int /*<<< orphan*/  AR_PHY_PAPRD_TRAINER_STAT1_PAPRD_AGC2_PWR ; 
 int /*<<< orphan*/  AR_PHY_PAPRD_TRAINER_STAT1_PAPRD_TRAIN_DONE ; 
 scalar_t__ AR_SREV_9485 (struct ath_hw*) ; 
 int /*<<< orphan*/  CALIBRATE ; 
 int PAPRD_IDEAL_AGC2_PWR_RANGE ; 
 int REG_READ_FIELD (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath9k_hw_common (struct ath_hw*) ; 
 int /*<<< orphan*/  ath_dbg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int) ; 

bool ar9003_paprd_is_done(struct ath_hw *ah)
{
	int paprd_done, agc2_pwr;

	paprd_done = REG_READ_FIELD(ah, AR_PHY_PAPRD_TRAINER_STAT1,
				AR_PHY_PAPRD_TRAINER_STAT1_PAPRD_TRAIN_DONE);

	if (AR_SREV_9485(ah))
		goto exit;

	if (paprd_done == 0x1) {
		agc2_pwr = REG_READ_FIELD(ah, AR_PHY_PAPRD_TRAINER_STAT1,
				AR_PHY_PAPRD_TRAINER_STAT1_PAPRD_AGC2_PWR);

		ath_dbg(ath9k_hw_common(ah), CALIBRATE,
			"AGC2_PWR = 0x%x training done = 0x%x\n",
			agc2_pwr, paprd_done);
	/*
	 * agc2_pwr range should not be less than 'IDEAL_AGC2_PWR_CHANGE'
	 * when the training is completely done, otherwise retraining is
	 * done to make sure the value is in ideal range
	 */
		if (agc2_pwr <= PAPRD_IDEAL_AGC2_PWR_RANGE)
			paprd_done = 0;
	}
exit:
	return !!paprd_done;
}
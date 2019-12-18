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
struct ath_common {int dummy; } ;

/* Variables and functions */
 int AH_WAIT_TIMEOUT ; 
 int /*<<< orphan*/  AR_PHY_AGC_CONTROL ; 
 int AR_PHY_AGC_CONTROL_CAL ; 
 int /*<<< orphan*/  CALIBRATE ; 
 int REG_READ (struct ath_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_WRITE (struct ath_hw*,int /*<<< orphan*/ ,int) ; 
 struct ath_common* ath9k_hw_common (struct ath_hw*) ; 
 int ath9k_hw_wait (struct ath_hw*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ath_dbg (struct ath_common*,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static bool do_ar9003_agc_cal(struct ath_hw *ah)
{
	struct ath_common *common = ath9k_hw_common(ah);
	bool status;

	REG_WRITE(ah, AR_PHY_AGC_CONTROL,
		  REG_READ(ah, AR_PHY_AGC_CONTROL) |
		  AR_PHY_AGC_CONTROL_CAL);

	status = ath9k_hw_wait(ah, AR_PHY_AGC_CONTROL,
			       AR_PHY_AGC_CONTROL_CAL,
			       0, AH_WAIT_TIMEOUT);
	if (!status) {
		ath_dbg(common, CALIBRATE,
			"offset calibration failed to complete in %d ms,"
			"noisy environment?\n",
			AH_WAIT_TIMEOUT / 1000);
		return false;
	}

	return true;
}
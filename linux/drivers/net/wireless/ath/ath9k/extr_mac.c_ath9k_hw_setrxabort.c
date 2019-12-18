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
typedef  int /*<<< orphan*/  u32 ;
struct ath_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AH_WAIT_TIMEOUT ; 
 int AR_DIAG_RX_ABORT ; 
 int AR_DIAG_RX_DIS ; 
 int /*<<< orphan*/  AR_DIAG_SW ; 
 int /*<<< orphan*/  AR_OBS_BUS_1 ; 
 int /*<<< orphan*/  AR_OBS_BUS_1_RX_STATE ; 
 int /*<<< orphan*/  REG_CLR_BIT (struct ath_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_READ (struct ath_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_SET_BIT (struct ath_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ath9k_hw_common (struct ath_hw*) ; 
 int /*<<< orphan*/  ath9k_hw_wait (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

bool ath9k_hw_setrxabort(struct ath_hw *ah, bool set)
{
	u32 reg;

	if (set) {
		REG_SET_BIT(ah, AR_DIAG_SW,
			    (AR_DIAG_RX_DIS | AR_DIAG_RX_ABORT));

		if (!ath9k_hw_wait(ah, AR_OBS_BUS_1, AR_OBS_BUS_1_RX_STATE,
				   0, AH_WAIT_TIMEOUT)) {
			REG_CLR_BIT(ah, AR_DIAG_SW,
				    (AR_DIAG_RX_DIS |
				     AR_DIAG_RX_ABORT));

			reg = REG_READ(ah, AR_OBS_BUS_1);
			ath_err(ath9k_hw_common(ah),
				"RX failed to go idle in 10 ms RXSM=0x%x\n",
				reg);

			return false;
		}
	} else {
		REG_CLR_BIT(ah, AR_DIAG_SW,
			    (AR_DIAG_RX_DIS | AR_DIAG_RX_ABORT));
	}

	return true;
}
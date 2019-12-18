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
struct ath_hw {TYPE_1__* caldata; } ;
struct ath9k_channel {int dummy; } ;
struct TYPE_2__ {int* caldac; int /*<<< orphan*/  cal_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR_PHY_65NM_RXRF_AGC (int) ; 
 int /*<<< orphan*/  AR_PHY_65NM_RXRF_AGC_AGC2G_CALDAC_OVR ; 
 int /*<<< orphan*/  AR_PHY_65NM_RXRF_AGC_AGC5G_CALDAC_OVR ; 
 int /*<<< orphan*/  AR_PHY_65NM_RXRF_AGC_AGC_OVERRIDE ; 
 scalar_t__ IS_CHAN_2GHZ (struct ath9k_channel*) ; 
 int /*<<< orphan*/  REG_RMW_FIELD (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RTT_DONE ; 
 int /*<<< orphan*/  SW_PKDET_DONE ; 
 int /*<<< orphan*/  ar9003_hw_rtt_disable (struct ath_hw*) ; 
 int /*<<< orphan*/  ar9003_hw_rtt_enable (struct ath_hw*) ; 
 int ar9003_hw_rtt_force_restore (struct ath_hw*) ; 
 int /*<<< orphan*/  ar9003_hw_rtt_load_hist (struct ath_hw*) ; 
 int /*<<< orphan*/  ar9003_hw_rtt_set_mask (struct ath_hw*,int) ; 
 int /*<<< orphan*/  ath9k_hw_common (struct ath_hw*) ; 
 int /*<<< orphan*/  ath9k_hw_rfbus_done (struct ath_hw*) ; 
 int /*<<< orphan*/  ath9k_hw_rfbus_req (struct ath_hw*) ; 
 int /*<<< orphan*/  ath_err (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

bool ar9003_hw_rtt_restore(struct ath_hw *ah, struct ath9k_channel *chan)
{
	bool restore;

	if (!ah->caldata)
		return false;

	if (test_bit(SW_PKDET_DONE, &ah->caldata->cal_flags)) {
		if (IS_CHAN_2GHZ(chan)){
			REG_RMW_FIELD(ah, AR_PHY_65NM_RXRF_AGC(0),
				      AR_PHY_65NM_RXRF_AGC_AGC2G_CALDAC_OVR,
				      ah->caldata->caldac[0]);
			REG_RMW_FIELD(ah, AR_PHY_65NM_RXRF_AGC(1),
				      AR_PHY_65NM_RXRF_AGC_AGC2G_CALDAC_OVR,
				      ah->caldata->caldac[1]);
		} else {
			REG_RMW_FIELD(ah, AR_PHY_65NM_RXRF_AGC(0),
				      AR_PHY_65NM_RXRF_AGC_AGC5G_CALDAC_OVR,
				      ah->caldata->caldac[0]);
			REG_RMW_FIELD(ah, AR_PHY_65NM_RXRF_AGC(1),
				      AR_PHY_65NM_RXRF_AGC_AGC5G_CALDAC_OVR,
				      ah->caldata->caldac[1]);
		}
		REG_RMW_FIELD(ah, AR_PHY_65NM_RXRF_AGC(1),
			      AR_PHY_65NM_RXRF_AGC_AGC_OVERRIDE, 0x1);
		REG_RMW_FIELD(ah, AR_PHY_65NM_RXRF_AGC(0),
			      AR_PHY_65NM_RXRF_AGC_AGC_OVERRIDE, 0x1);
	}

	if (!test_bit(RTT_DONE, &ah->caldata->cal_flags))
		return false;

	ar9003_hw_rtt_enable(ah);

	if (test_bit(SW_PKDET_DONE, &ah->caldata->cal_flags))
		ar9003_hw_rtt_set_mask(ah, 0x30);
	else
		ar9003_hw_rtt_set_mask(ah, 0x10);

	if (!ath9k_hw_rfbus_req(ah)) {
		ath_err(ath9k_hw_common(ah), "Could not stop baseband\n");
		restore = false;
		goto fail;
	}

	ar9003_hw_rtt_load_hist(ah);
	restore = ar9003_hw_rtt_force_restore(ah);

fail:
	ath9k_hw_rfbus_done(ah);
	ar9003_hw_rtt_disable(ah);
	return restore;
}
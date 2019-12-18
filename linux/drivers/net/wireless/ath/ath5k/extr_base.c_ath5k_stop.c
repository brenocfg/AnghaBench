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
struct ieee80211_hw {struct ath5k_hw* priv; } ;
struct ath5k_hw {int /*<<< orphan*/  tx_complete_work; int /*<<< orphan*/  status; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH5K_DBG (struct ath5k_hw*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ATH5K_DEBUG_RESET ; 
 int /*<<< orphan*/  ATH_STAT_INVALID ; 
 int /*<<< orphan*/  ATH_STAT_STARTED ; 
 int ath5k_hw_on_hold (struct ath5k_hw*) ; 
 int /*<<< orphan*/  ath5k_modparam_no_hw_rfkill_switch ; 
 int /*<<< orphan*/  ath5k_rfkill_hw_stop (struct ath5k_hw*) ; 
 int ath5k_stop_locked (struct ath5k_hw*) ; 
 int /*<<< orphan*/  ath5k_stop_tasklets (struct ath5k_hw*) ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void ath5k_stop(struct ieee80211_hw *hw)
{
	struct ath5k_hw *ah = hw->priv;
	int ret;

	mutex_lock(&ah->lock);
	ret = ath5k_stop_locked(ah);
	if (ret == 0 && !test_bit(ATH_STAT_INVALID, ah->status)) {
		/*
		 * Don't set the card in full sleep mode!
		 *
		 * a) When the device is in this state it must be carefully
		 * woken up or references to registers in the PCI clock
		 * domain may freeze the bus (and system).  This varies
		 * by chip and is mostly an issue with newer parts
		 * (madwifi sources mentioned srev >= 0x78) that go to
		 * sleep more quickly.
		 *
		 * b) On older chips full sleep results a weird behaviour
		 * during wakeup. I tested various cards with srev < 0x78
		 * and they don't wake up after module reload, a second
		 * module reload is needed to bring the card up again.
		 *
		 * Until we figure out what's going on don't enable
		 * full chip reset on any chip (this is what Legacy HAL
		 * and Sam's HAL do anyway). Instead Perform a full reset
		 * on the device (same as initial state after attach) and
		 * leave it idle (keep MAC/BB on warm reset) */
		ret = ath5k_hw_on_hold(ah);

		ATH5K_DBG(ah, ATH5K_DEBUG_RESET,
				"putting device to sleep\n");
	}

	mutex_unlock(&ah->lock);

	ath5k_stop_tasklets(ah);

	clear_bit(ATH_STAT_STARTED, ah->status);
	cancel_delayed_work_sync(&ah->tx_complete_work);

	if (!ath5k_modparam_no_hw_rfkill_switch)
		ath5k_rfkill_hw_stop(ah);
}
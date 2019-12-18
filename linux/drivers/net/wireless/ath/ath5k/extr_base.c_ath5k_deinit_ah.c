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
struct ieee80211_hw {int dummy; } ;
struct ath5k_hw {int /*<<< orphan*/  irq; int /*<<< orphan*/  bhalq; struct ieee80211_hw* hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  ath5k_desc_free (struct ath5k_hw*) ; 
 int /*<<< orphan*/  ath5k_hw_deinit (struct ath5k_hw*) ; 
 int /*<<< orphan*/  ath5k_hw_release_tx_queue (struct ath5k_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath5k_sysfs_unregister (struct ath5k_hw*) ; 
 int /*<<< orphan*/  ath5k_txq_release (struct ath5k_hw*) ; 
 int /*<<< orphan*/  ath5k_unregister_leds (struct ath5k_hw*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct ath5k_hw*) ; 
 int /*<<< orphan*/  ieee80211_unregister_hw (struct ieee80211_hw*) ; 

void
ath5k_deinit_ah(struct ath5k_hw *ah)
{
	struct ieee80211_hw *hw = ah->hw;

	/*
	 * NB: the order of these is important:
	 * o call the 802.11 layer before detaching ath5k_hw to
	 *   ensure callbacks into the driver to delete global
	 *   key cache entries can be handled
	 * o reclaim the tx queue data structures after calling
	 *   the 802.11 layer as we'll get called back to reclaim
	 *   node state and potentially want to use them
	 * o to cleanup the tx queues the hal is called, so detach
	 *   it last
	 * XXX: ??? detach ath5k_hw ???
	 * Other than that, it's straightforward...
	 */
	ieee80211_unregister_hw(hw);
	ath5k_desc_free(ah);
	ath5k_txq_release(ah);
	ath5k_hw_release_tx_queue(ah, ah->bhalq);
	ath5k_unregister_leds(ah);

	ath5k_sysfs_unregister(ah);
	/*
	 * NB: can't reclaim these until after ieee80211_ifdetach
	 * returns because we'll get called back to reclaim node
	 * state and potentially want to use them.
	 */
	ath5k_hw_deinit(ah);
	free_irq(ah->irq, ah);
}
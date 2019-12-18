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
typedef  int /*<<< orphan*/  u32 ;
struct ieee80211_hw {struct ath_softc* priv; } ;
struct ath_softc {int /*<<< orphan*/  hw_check_work; int /*<<< orphan*/  sc_pcu_lock; int /*<<< orphan*/  tx_wait; int /*<<< orphan*/  chan_lock; TYPE_1__* cur_chan; struct ath_hw* sc_ah; } ;
struct ath_hw {int ah_flags; } ;
struct ath_common {int /*<<< orphan*/  op_flags; } ;
struct TYPE_2__ {int flush_timeout; } ;

/* Variables and functions */
 int AH_UNPLUGGED ; 
 int /*<<< orphan*/  ANY ; 
 int /*<<< orphan*/  ATH_HW_CHECK_POLL_INT ; 
 int /*<<< orphan*/  ATH_OP_INVALID ; 
 int /*<<< orphan*/  CHAN_CTX ; 
 int HZ ; 
 int /*<<< orphan*/  ath9k_has_tx_pending (struct ath_softc*,int) ; 
 struct ath_common* ath9k_hw_common (struct ath_hw*) ; 
 int /*<<< orphan*/  ath9k_ps_restore (struct ath_softc*) ; 
 int /*<<< orphan*/  ath9k_ps_wakeup (struct ath_softc*) ; 
 int /*<<< orphan*/  ath_dbg (struct ath_common*,int /*<<< orphan*/ ,char*,...) ; 
 int ath_drain_all_txq (struct ath_softc*) ; 
 int /*<<< orphan*/  ath_reset (struct ath_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee80211_queue_delayed_work (struct ieee80211_hw*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jiffies_to_msecs (int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ wait_event_timeout (int /*<<< orphan*/ ,int,int) ; 

void __ath9k_flush(struct ieee80211_hw *hw, u32 queues, bool drop,
		   bool sw_pending, bool timeout_override)
{
	struct ath_softc *sc = hw->priv;
	struct ath_hw *ah = sc->sc_ah;
	struct ath_common *common = ath9k_hw_common(ah);
	int timeout;
	bool drain_txq;

	cancel_delayed_work_sync(&sc->hw_check_work);

	if (ah->ah_flags & AH_UNPLUGGED) {
		ath_dbg(common, ANY, "Device has been unplugged!\n");
		return;
	}

	if (test_bit(ATH_OP_INVALID, &common->op_flags)) {
		ath_dbg(common, ANY, "Device not present\n");
		return;
	}

	spin_lock_bh(&sc->chan_lock);
	if (timeout_override)
		timeout = HZ / 5;
	else
		timeout = sc->cur_chan->flush_timeout;
	spin_unlock_bh(&sc->chan_lock);

	ath_dbg(common, CHAN_CTX,
		"Flush timeout: %d\n", jiffies_to_msecs(timeout));

	if (wait_event_timeout(sc->tx_wait, !ath9k_has_tx_pending(sc, sw_pending),
			       timeout) > 0)
		drop = false;

	if (drop) {
		ath9k_ps_wakeup(sc);
		spin_lock_bh(&sc->sc_pcu_lock);
		drain_txq = ath_drain_all_txq(sc);
		spin_unlock_bh(&sc->sc_pcu_lock);

		if (!drain_txq)
			ath_reset(sc, NULL);

		ath9k_ps_restore(sc);
	}

	ieee80211_queue_delayed_work(hw, &sc->hw_check_work,
				     ATH_HW_CHECK_POLL_INT);
}
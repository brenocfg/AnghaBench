#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {scalar_t__ data; } ;
struct ieee80211_tx_control {int /*<<< orphan*/  sta; } ;
struct ieee80211_hw {struct ath_softc* priv; } ;
struct ieee80211_hdr {int /*<<< orphan*/  frame_control; } ;
struct ath_tx_control {TYPE_3__* txq; int /*<<< orphan*/  sta; } ;
struct TYPE_7__ {TYPE_3__** txq_map; } ;
struct ath_softc {TYPE_2__ tx; TYPE_4__* sc_ah; int /*<<< orphan*/  sc_pm_lock; int /*<<< orphan*/  ps_flags; scalar_t__ ps_enabled; } ;
struct ath_common {int dummy; } ;
struct TYPE_6__ {int hw_caps; } ;
struct TYPE_9__ {scalar_t__ power_mode; TYPE_1__ caps; } ;
struct TYPE_8__ {int /*<<< orphan*/  axq_qnum; } ;

/* Variables and functions */
 int ATH9K_HW_CAP_AUTOSLEEP ; 
 scalar_t__ ATH9K_PM_FULL_SLEEP ; 
 scalar_t__ ATH9K_PM_NETWORK_SLEEP ; 
 int /*<<< orphan*/  IEEE80211_FCTL_PM ; 
 int /*<<< orphan*/  PS ; 
 int /*<<< orphan*/  PS_WAIT_FOR_PSPOLL_DATA ; 
 int /*<<< orphan*/  PS_WAIT_FOR_TX_ACK ; 
 int /*<<< orphan*/  TX_STAT_INC (struct ath_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XMIT ; 
 struct ath_common* ath9k_hw_common (TYPE_4__*) ; 
 int /*<<< orphan*/  ath9k_hw_setrxabort (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath9k_ps_restore (struct ath_softc*) ; 
 int /*<<< orphan*/  ath9k_ps_wakeup (struct ath_softc*) ; 
 int /*<<< orphan*/  ath_dbg (struct ath_common*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ath_err (struct ath_common*,char*) ; 
 scalar_t__ ath_tx_start (struct ieee80211_hw*,struct sk_buff*,struct ath_tx_control*) ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_free_txskb (struct ieee80211_hw*,struct sk_buff*) ; 
 int /*<<< orphan*/  ieee80211_has_pm (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_is_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_is_nullfunc (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_is_pspoll (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ath_tx_control*,int /*<<< orphan*/ ,int) ; 
 size_t skb_get_queue_mapping (struct sk_buff*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  txfailed ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void ath9k_tx(struct ieee80211_hw *hw,
		     struct ieee80211_tx_control *control,
		     struct sk_buff *skb)
{
	struct ath_softc *sc = hw->priv;
	struct ath_common *common = ath9k_hw_common(sc->sc_ah);
	struct ath_tx_control txctl;
	struct ieee80211_hdr *hdr = (struct ieee80211_hdr *) skb->data;
	unsigned long flags;

	if (sc->ps_enabled) {
		/*
		 * mac80211 does not set PM field for normal data frames, so we
		 * need to update that based on the current PS mode.
		 */
		if (ieee80211_is_data(hdr->frame_control) &&
		    !ieee80211_is_nullfunc(hdr->frame_control) &&
		    !ieee80211_has_pm(hdr->frame_control)) {
			ath_dbg(common, PS,
				"Add PM=1 for a TX frame while in PS mode\n");
			hdr->frame_control |= cpu_to_le16(IEEE80211_FCTL_PM);
		}
	}

	if (unlikely(sc->sc_ah->power_mode == ATH9K_PM_NETWORK_SLEEP)) {
		/*
		 * We are using PS-Poll and mac80211 can request TX while in
		 * power save mode. Need to wake up hardware for the TX to be
		 * completed and if needed, also for RX of buffered frames.
		 */
		ath9k_ps_wakeup(sc);
		spin_lock_irqsave(&sc->sc_pm_lock, flags);
		if (!(sc->sc_ah->caps.hw_caps & ATH9K_HW_CAP_AUTOSLEEP))
			ath9k_hw_setrxabort(sc->sc_ah, 0);
		if (ieee80211_is_pspoll(hdr->frame_control)) {
			ath_dbg(common, PS,
				"Sending PS-Poll to pick a buffered frame\n");
			sc->ps_flags |= PS_WAIT_FOR_PSPOLL_DATA;
		} else {
			ath_dbg(common, PS, "Wake up to complete TX\n");
			sc->ps_flags |= PS_WAIT_FOR_TX_ACK;
		}
		/*
		 * The actual restore operation will happen only after
		 * the ps_flags bit is cleared. We are just dropping
		 * the ps_usecount here.
		 */
		spin_unlock_irqrestore(&sc->sc_pm_lock, flags);
		ath9k_ps_restore(sc);
	}

	/*
	 * Cannot tx while the hardware is in full sleep, it first needs a full
	 * chip reset to recover from that
	 */
	if (unlikely(sc->sc_ah->power_mode == ATH9K_PM_FULL_SLEEP)) {
		ath_err(common, "TX while HW is in FULL_SLEEP mode\n");
		goto exit;
	}

	memset(&txctl, 0, sizeof(struct ath_tx_control));
	txctl.txq = sc->tx.txq_map[skb_get_queue_mapping(skb)];
	txctl.sta = control->sta;

	ath_dbg(common, XMIT, "transmitting packet, skb: %p\n", skb);

	if (ath_tx_start(hw, skb, &txctl) != 0) {
		ath_dbg(common, XMIT, "TX failed\n");
		TX_STAT_INC(sc, txctl.txq->axq_qnum, txfailed);
		goto exit;
	}

	return;
exit:
	ieee80211_free_txskb(hw, skb);
}
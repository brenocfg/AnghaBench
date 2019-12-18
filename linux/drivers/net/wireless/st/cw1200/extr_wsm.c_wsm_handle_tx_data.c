#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct wsm_tx {int /*<<< orphan*/  packet_id; int /*<<< orphan*/  queue_id; } ;
struct TYPE_8__ {TYPE_3__* hw_key; } ;
struct ieee80211_tx_info {TYPE_4__ control; } ;
struct ieee80211_hdr {int /*<<< orphan*/  frame_control; } ;
struct cw1200_txpriv {size_t offset; int /*<<< orphan*/  raw_link_id; } ;
struct cw1200_queue {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  probe_work; } ;
struct cw1200_common {int mode; int link_id_map; scalar_t__ wep_default_key_id; int /*<<< orphan*/  wep_key_work; int /*<<< orphan*/  workqueue; int /*<<< orphan*/  pending_frame_id; TYPE_2__ scan; int /*<<< orphan*/  unjoin_work; int /*<<< orphan*/  bss_loss_lock; int /*<<< orphan*/  bss_loss_confirm_id; scalar_t__ bss_loss_state; int /*<<< orphan*/  join_status; TYPE_1__* hw; } ;
typedef  int /*<<< orphan*/  __le16 ;
struct TYPE_7__ {scalar_t__ keyidx; scalar_t__ cipher; } ;
struct TYPE_5__ {int /*<<< orphan*/  wiphy; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CW1200_JOIN_STATUS_IBSS ; 
 int /*<<< orphan*/  CW1200_JOIN_STATUS_MONITOR ; 
 int /*<<< orphan*/  CW1200_JOIN_STATUS_PRE_STA ; 
 int /*<<< orphan*/  CW1200_MAX_REQUEUE_ATTEMPTS ; 
#define  NL80211_IFTYPE_ADHOC 132 
#define  NL80211_IFTYPE_AP 131 
#define  NL80211_IFTYPE_MESH_POINT 130 
#define  NL80211_IFTYPE_MONITOR 129 
#define  NL80211_IFTYPE_STATION 128 
 scalar_t__ WLAN_CIPHER_SUITE_WEP104 ; 
 scalar_t__ WLAN_CIPHER_SUITE_WEP40 ; 
 int /*<<< orphan*/  WSM_QUEUE_VOICE ; 
 int /*<<< orphan*/  cw1200_queue_get_generation (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cw1200_queue_remove (struct cw1200_queue*,int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_has_protected (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_is_deauth (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_is_nullfunc (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_is_probe_req (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wiphy_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wsm_lock_tx_async (struct cw1200_common*) ; 
 int /*<<< orphan*/  wsm_unlock_tx (struct cw1200_common*) ; 

__attribute__((used)) static bool wsm_handle_tx_data(struct cw1200_common *priv,
			       struct wsm_tx *wsm,
			       const struct ieee80211_tx_info *tx_info,
			       const struct cw1200_txpriv *txpriv,
			       struct cw1200_queue *queue)
{
	bool handled = false;
	const struct ieee80211_hdr *frame =
		(struct ieee80211_hdr *)&((u8 *)wsm)[txpriv->offset];
	__le16 fctl = frame->frame_control;
	enum {
		do_probe,
		do_drop,
		do_wep,
		do_tx,
	} action = do_tx;

	switch (priv->mode) {
	case NL80211_IFTYPE_STATION:
		if (priv->join_status == CW1200_JOIN_STATUS_MONITOR)
			action = do_tx;
		else if (priv->join_status < CW1200_JOIN_STATUS_PRE_STA)
			action = do_drop;
		break;
	case NL80211_IFTYPE_AP:
		if (!priv->join_status) {
			action = do_drop;
		} else if (!(BIT(txpriv->raw_link_id) &
			     (BIT(0) | priv->link_id_map))) {
			wiphy_warn(priv->hw->wiphy,
				   "A frame with expired link id is dropped.\n");
			action = do_drop;
		}
		if (cw1200_queue_get_generation(wsm->packet_id) >
				CW1200_MAX_REQUEUE_ATTEMPTS) {
			/* HACK!!! WSM324 firmware has tendency to requeue
			 * multicast frames in a loop, causing performance
			 * drop and high power consumption of the driver.
			 * In this situation it is better just to drop
			 * the problematic frame.
			 */
			wiphy_warn(priv->hw->wiphy,
				   "Too many attempts to requeue a frame; dropped.\n");
			action = do_drop;
		}
		break;
	case NL80211_IFTYPE_ADHOC:
		if (priv->join_status != CW1200_JOIN_STATUS_IBSS)
			action = do_drop;
		break;
	case NL80211_IFTYPE_MESH_POINT:
		action = do_tx; /* TODO:  Test me! */
		break;
	case NL80211_IFTYPE_MONITOR:
	default:
		action = do_drop;
		break;
	}

	if (action == do_tx) {
		if (ieee80211_is_nullfunc(fctl)) {
			spin_lock(&priv->bss_loss_lock);
			if (priv->bss_loss_state) {
				priv->bss_loss_confirm_id = wsm->packet_id;
				wsm->queue_id = WSM_QUEUE_VOICE;
			}
			spin_unlock(&priv->bss_loss_lock);
		} else if (ieee80211_is_probe_req(fctl)) {
			action = do_probe;
		} else if (ieee80211_is_deauth(fctl) &&
			   priv->mode != NL80211_IFTYPE_AP) {
			pr_debug("[WSM] Issue unjoin command due to tx deauth.\n");
			wsm_lock_tx_async(priv);
			if (queue_work(priv->workqueue,
				       &priv->unjoin_work) <= 0)
				wsm_unlock_tx(priv);
		} else if (ieee80211_has_protected(fctl) &&
			   tx_info->control.hw_key &&
			   tx_info->control.hw_key->keyidx != priv->wep_default_key_id &&
			   (tx_info->control.hw_key->cipher == WLAN_CIPHER_SUITE_WEP40 ||
			    tx_info->control.hw_key->cipher == WLAN_CIPHER_SUITE_WEP104)) {
			action = do_wep;
		}
	}

	switch (action) {
	case do_probe:
		/* An interesting FW "feature". Device filters probe responses.
		 * The easiest way to get it back is to convert
		 * probe request into WSM start_scan command.
		 */
		pr_debug("[WSM] Convert probe request to scan.\n");
		wsm_lock_tx_async(priv);
		priv->pending_frame_id = wsm->packet_id;
		if (queue_delayed_work(priv->workqueue,
				       &priv->scan.probe_work, 0) <= 0)
			wsm_unlock_tx(priv);
		handled = true;
		break;
	case do_drop:
		pr_debug("[WSM] Drop frame (0x%.4X).\n", fctl);
		BUG_ON(cw1200_queue_remove(queue, wsm->packet_id));
		handled = true;
		break;
	case do_wep:
		pr_debug("[WSM] Issue set_default_wep_key.\n");
		wsm_lock_tx_async(priv);
		priv->wep_default_key_id = tx_info->control.hw_key->keyidx;
		priv->pending_frame_id = wsm->packet_id;
		if (queue_work(priv->workqueue, &priv->wep_key_work) <= 0)
			wsm_unlock_tx(priv);
		handled = true;
		break;
	case do_tx:
		pr_debug("[WSM] Transmit frame.\n");
		break;
	default:
		/* Do nothing */
		break;
	}
	return handled;
}
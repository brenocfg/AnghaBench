#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct wsm_tx {int /*<<< orphan*/  flags; } ;
struct sk_buff {int /*<<< orphan*/  len; scalar_t__ data; } ;
struct ieee80211_tx_control {TYPE_1__* sta; } ;
struct ieee80211_sta {int dummy; } ;
struct ieee80211_hw {struct cw1200_common* priv; } ;
struct ieee80211_hdr {int /*<<< orphan*/  frame_control; } ;
struct TYPE_5__ {int /*<<< orphan*/  tid; int /*<<< orphan*/  raw_link_id; int /*<<< orphan*/  link_id; int /*<<< orphan*/  rate_id; } ;
struct cw1200_txinfo {int queue; TYPE_2__ txpriv; struct sk_buff* skb; TYPE_1__* sta; struct cw1200_sta_priv* sta_priv; struct ieee80211_hdr* hdr; int /*<<< orphan*/  da; int /*<<< orphan*/  hdrlen; int /*<<< orphan*/  tx_info; } ;
struct cw1200_sta_priv {int dummy; } ;
struct cw1200_common {int /*<<< orphan*/  ps_state_lock; int /*<<< orphan*/ * tx_queue; scalar_t__ bh_error; } ;
struct TYPE_4__ {int /*<<< orphan*/  drv_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CW1200_INVALID_RATE_ID ; 
 int /*<<< orphan*/  CW1200_MAX_TID ; 
 int ENOMEM ; 
 int /*<<< orphan*/  IEEE80211_SKB_CB (struct sk_buff*) ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  cw1200_bh_wakeup (struct cw1200_common*) ; 
 int /*<<< orphan*/  cw1200_queue_put (int /*<<< orphan*/ *,struct sk_buff*,TYPE_2__*) ; 
 int /*<<< orphan*/  cw1200_skb_dtor (struct cw1200_common*,struct sk_buff*,TYPE_2__*) ; 
 int cw1200_tx_h_action (struct cw1200_common*,struct cw1200_txinfo*) ; 
 int cw1200_tx_h_align (struct cw1200_common*,struct cw1200_txinfo*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cw1200_tx_h_bt (struct cw1200_common*,struct cw1200_txinfo*,struct wsm_tx*) ; 
 int cw1200_tx_h_calc_link_ids (struct cw1200_common*,struct cw1200_txinfo*) ; 
 int /*<<< orphan*/  cw1200_tx_h_calc_tid (struct cw1200_common*,struct cw1200_txinfo*) ; 
 int cw1200_tx_h_crypt (struct cw1200_common*,struct cw1200_txinfo*) ; 
 int /*<<< orphan*/  cw1200_tx_h_pm (struct cw1200_common*,struct cw1200_txinfo*) ; 
 int cw1200_tx_h_pm_state (struct cw1200_common*,struct cw1200_txinfo*) ; 
 int cw1200_tx_h_rate_policy (struct cw1200_common*,struct cw1200_txinfo*,struct wsm_tx*) ; 
 struct wsm_tx* cw1200_tx_h_wsm (struct cw1200_common*,struct cw1200_txinfo*) ; 
 int /*<<< orphan*/  ieee80211_get_DA (struct ieee80211_hdr*) ; 
 int /*<<< orphan*/  ieee80211_hdrlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_sta_set_buffered (struct ieee80211_sta*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ieee80211_sta* rcu_dereference (TYPE_1__*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int skb_get_queue_mapping (struct sk_buff*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void cw1200_tx(struct ieee80211_hw *dev,
	       struct ieee80211_tx_control *control,
	       struct sk_buff *skb)
{
	struct cw1200_common *priv = dev->priv;
	struct cw1200_txinfo t = {
		.skb = skb,
		.queue = skb_get_queue_mapping(skb),
		.tx_info = IEEE80211_SKB_CB(skb),
		.hdr = (struct ieee80211_hdr *)skb->data,
		.txpriv.tid = CW1200_MAX_TID,
		.txpriv.rate_id = CW1200_INVALID_RATE_ID,
	};
	struct ieee80211_sta *sta;
	struct wsm_tx *wsm;
	bool tid_update = 0;
	u8 flags = 0;
	int ret;

	if (priv->bh_error)
		goto drop;

	t.hdrlen = ieee80211_hdrlen(t.hdr->frame_control);
	t.da = ieee80211_get_DA(t.hdr);
	if (control) {
		t.sta = control->sta;
		t.sta_priv = (struct cw1200_sta_priv *)&t.sta->drv_priv;
	}

	if (WARN_ON(t.queue >= 4))
		goto drop;

	ret = cw1200_tx_h_calc_link_ids(priv, &t);
	if (ret)
		goto drop;

	pr_debug("[TX] TX %d bytes (queue: %d, link_id: %d (%d)).\n",
		 skb->len, t.queue, t.txpriv.link_id,
		 t.txpriv.raw_link_id);

	cw1200_tx_h_pm(priv, &t);
	cw1200_tx_h_calc_tid(priv, &t);
	ret = cw1200_tx_h_crypt(priv, &t);
	if (ret)
		goto drop;
	ret = cw1200_tx_h_align(priv, &t, &flags);
	if (ret)
		goto drop;
	ret = cw1200_tx_h_action(priv, &t);
	if (ret)
		goto drop;
	wsm = cw1200_tx_h_wsm(priv, &t);
	if (!wsm) {
		ret = -ENOMEM;
		goto drop;
	}
	wsm->flags |= flags;
	cw1200_tx_h_bt(priv, &t, wsm);
	ret = cw1200_tx_h_rate_policy(priv, &t, wsm);
	if (ret)
		goto drop;

	rcu_read_lock();
	sta = rcu_dereference(t.sta);

	spin_lock_bh(&priv->ps_state_lock);
	{
		tid_update = cw1200_tx_h_pm_state(priv, &t);
		BUG_ON(cw1200_queue_put(&priv->tx_queue[t.queue],
					t.skb, &t.txpriv));
	}
	spin_unlock_bh(&priv->ps_state_lock);

	if (tid_update && sta)
		ieee80211_sta_set_buffered(sta, t.txpriv.tid, true);

	rcu_read_unlock();

	cw1200_bh_wakeup(priv);

	return;

drop:
	cw1200_skb_dtor(priv, skb, &t.txpriv);
	return;
}
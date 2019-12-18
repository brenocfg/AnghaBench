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
struct ieee80211_vif {int dummy; } ;
struct ieee80211_sta {int /*<<< orphan*/  drv_priv; } ;
struct ieee80211_hw {struct cw1200_common* priv; } ;
struct cw1200_sta_priv {int link_id; } ;
struct cw1200_link_entry {int /*<<< orphan*/  timestamp; int /*<<< orphan*/  status; } ;
struct cw1200_common {scalar_t__ mode; int /*<<< orphan*/  workqueue; int /*<<< orphan*/  ps_state_lock; int /*<<< orphan*/  link_id_work; struct cw1200_link_entry* link_id_db; } ;

/* Variables and functions */
 int /*<<< orphan*/  CW1200_LINK_RESERVE ; 
 scalar_t__ NL80211_IFTYPE_AP ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jiffies ; 
 scalar_t__ queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wsm_lock_tx_async (struct cw1200_common*) ; 
 int /*<<< orphan*/  wsm_unlock_tx (struct cw1200_common*) ; 

int cw1200_sta_remove(struct ieee80211_hw *hw, struct ieee80211_vif *vif,
		      struct ieee80211_sta *sta)
{
	struct cw1200_common *priv = hw->priv;
	struct cw1200_sta_priv *sta_priv =
			(struct cw1200_sta_priv *)&sta->drv_priv;
	struct cw1200_link_entry *entry;

	if (priv->mode != NL80211_IFTYPE_AP || !sta_priv->link_id)
		return 0;

	entry = &priv->link_id_db[sta_priv->link_id - 1];
	spin_lock_bh(&priv->ps_state_lock);
	entry->status = CW1200_LINK_RESERVE;
	entry->timestamp = jiffies;
	wsm_lock_tx_async(priv);
	if (queue_work(priv->workqueue, &priv->link_id_work) <= 0)
		wsm_unlock_tx(priv);
	spin_unlock_bh(&priv->ps_state_lock);
	flush_workqueue(priv->workqueue);
	return 0;
}
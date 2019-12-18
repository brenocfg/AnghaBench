#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct cw1200_link_entry {scalar_t__ status; unsigned long timestamp; int /*<<< orphan*/  rx_queue; int /*<<< orphan*/  buffered; int /*<<< orphan*/  mac; } ;
struct TYPE_3__ {int /*<<< orphan*/ * link_map_cache; } ;
struct cw1200_common {int /*<<< orphan*/  ps_state_lock; TYPE_2__* hw; int /*<<< orphan*/  link_id_work; int /*<<< orphan*/  workqueue; struct cw1200_link_entry* link_id_db; TYPE_1__ tx_queue_stats; } ;
struct TYPE_4__ {int /*<<< orphan*/  wiphy; } ;

/* Variables and functions */
 scalar_t__ CW1200_LINK_HARD ; 
 scalar_t__ CW1200_LINK_RESERVE ; 
 int CW1200_MAX_STA_IN_AP_MODE ; 
 int /*<<< orphan*/  CW1200_MAX_TID ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 
 scalar_t__ queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wiphy_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wsm_lock_tx_async (struct cw1200_common*) ; 
 int /*<<< orphan*/  wsm_unlock_tx (struct cw1200_common*) ; 

int cw1200_alloc_link_id(struct cw1200_common *priv, const u8 *mac)
{
	int i, ret = 0;
	unsigned long max_inactivity = 0;
	unsigned long now = jiffies;

	spin_lock_bh(&priv->ps_state_lock);
	for (i = 0; i < CW1200_MAX_STA_IN_AP_MODE; ++i) {
		if (!priv->link_id_db[i].status) {
			ret = i + 1;
			break;
		} else if (priv->link_id_db[i].status != CW1200_LINK_HARD &&
			   !priv->tx_queue_stats.link_map_cache[i + 1]) {
			unsigned long inactivity =
				now - priv->link_id_db[i].timestamp;
			if (inactivity < max_inactivity)
				continue;
			max_inactivity = inactivity;
			ret = i + 1;
		}
	}
	if (ret) {
		struct cw1200_link_entry *entry = &priv->link_id_db[ret - 1];
		pr_debug("[AP] STA added, link_id: %d\n", ret);
		entry->status = CW1200_LINK_RESERVE;
		memcpy(&entry->mac, mac, ETH_ALEN);
		memset(&entry->buffered, 0, CW1200_MAX_TID);
		skb_queue_head_init(&entry->rx_queue);
		wsm_lock_tx_async(priv);
		if (queue_work(priv->workqueue, &priv->link_id_work) <= 0)
			wsm_unlock_tx(priv);
	} else {
		wiphy_info(priv->hw->wiphy,
			   "[AP] Early: no more link IDs available.\n");
	}

	spin_unlock_bh(&priv->ps_state_lock);
	return ret;
}
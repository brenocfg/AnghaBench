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
typedef  int /*<<< orphan*/  u8 ;
struct mwifiex_ra_list_tbl {int /*<<< orphan*/  list; scalar_t__ total_pkt_count; scalar_t__ tx_paused; } ;
struct TYPE_2__ {int /*<<< orphan*/  ra_list_spinlock; int /*<<< orphan*/  tx_pkts_queued; int /*<<< orphan*/ * pkts_paused; } ;
struct mwifiex_private {TYPE_1__ wmm; } ;

/* Variables and functions */
 int MAX_NUM_TID ; 
 int /*<<< orphan*/  atomic_sub (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct mwifiex_ra_list_tbl*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mwifiex_wmm_del_pkts_in_ralist_node (struct mwifiex_private*,struct mwifiex_ra_list_tbl*) ; 
 struct mwifiex_ra_list_tbl* mwifiex_wmm_get_ralist_node (struct mwifiex_private*,int,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void
mwifiex_wmm_del_peer_ra_list(struct mwifiex_private *priv, const u8 *ra_addr)
{
	struct mwifiex_ra_list_tbl *ra_list;
	int i;

	spin_lock_bh(&priv->wmm.ra_list_spinlock);

	for (i = 0; i < MAX_NUM_TID; ++i) {
		ra_list = mwifiex_wmm_get_ralist_node(priv, i, ra_addr);

		if (!ra_list)
			continue;
		mwifiex_wmm_del_pkts_in_ralist_node(priv, ra_list);
		if (ra_list->tx_paused)
			priv->wmm.pkts_paused[i] -= ra_list->total_pkt_count;
		else
			atomic_sub(ra_list->total_pkt_count,
				   &priv->wmm.tx_pkts_queued);
		list_del(&ra_list->list);
		kfree(ra_list);
	}
	spin_unlock_bh(&priv->wmm.ra_list_spinlock);
}
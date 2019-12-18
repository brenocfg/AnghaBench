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
struct TYPE_4__ {int /*<<< orphan*/  ra_list_spinlock; TYPE_1__* tid_tbl_ptr; } ;
struct mwifiex_private {int del_list_idx; TYPE_2__ wmm; } ;
struct list_head {int dummy; } ;
struct TYPE_3__ {struct list_head ra_list; } ;

/* Variables and functions */
 int MAX_NUM_TID ; 
 scalar_t__ mwifiex_uap_del_tx_pkts_in_ralist (struct mwifiex_private*,struct list_head*,int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mwifiex_uap_cleanup_tx_queues(struct mwifiex_private *priv)
{
	struct list_head *ra_list;
	int i;

	spin_lock_bh(&priv->wmm.ra_list_spinlock);

	for (i = 0; i < MAX_NUM_TID; i++, priv->del_list_idx++) {
		if (priv->del_list_idx == MAX_NUM_TID)
			priv->del_list_idx = 0;
		ra_list = &priv->wmm.tid_tbl_ptr[priv->del_list_idx].ra_list;
		if (mwifiex_uap_del_tx_pkts_in_ralist(priv, ra_list, i)) {
			priv->del_list_idx++;
			break;
		}
	}

	spin_unlock_bh(&priv->wmm.ra_list_spinlock);
}
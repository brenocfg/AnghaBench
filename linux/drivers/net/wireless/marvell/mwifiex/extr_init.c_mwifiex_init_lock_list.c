#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* tid_tbl_ptr; int /*<<< orphan*/  ra_list_spinlock; } ;
struct mwifiex_private {int /*<<< orphan*/  ack_status_frames; int /*<<< orphan*/  ack_status_lock; int /*<<< orphan*/  rx_reorder_tbl_lock; int /*<<< orphan*/  tx_ba_stream_tbl_lock; int /*<<< orphan*/  bypass_txq; int /*<<< orphan*/  tdls_txq; int /*<<< orphan*/  auto_tdls_list; int /*<<< orphan*/  sta_list; int /*<<< orphan*/  rx_reorder_tbl_ptr; int /*<<< orphan*/  tx_ba_stream_tbl_ptr; TYPE_3__ wmm; int /*<<< orphan*/  auto_tdls_lock; int /*<<< orphan*/  sta_list_spinlock; int /*<<< orphan*/  curr_bcn_buf_lock; } ;
struct mwifiex_adapter {size_t priv_num; struct mwifiex_private** priv; TYPE_1__* bss_prio_tbl; int /*<<< orphan*/  tx_data_q; int /*<<< orphan*/  rx_data_q; int /*<<< orphan*/  rx_proc_lock; int /*<<< orphan*/  scan_pending_q_lock; int /*<<< orphan*/  cmd_pending_q_lock; int /*<<< orphan*/  cmd_free_q_lock; int /*<<< orphan*/  scan_pending_q; int /*<<< orphan*/  cmd_pending_q; int /*<<< orphan*/  cmd_free_q; int /*<<< orphan*/  queue_lock; int /*<<< orphan*/  mwifiex_cmd_lock; int /*<<< orphan*/  main_proc_lock; int /*<<< orphan*/  int_lock; } ;
typedef  size_t s32 ;
struct TYPE_5__ {int /*<<< orphan*/  ra_list; } ;
struct TYPE_4__ {int /*<<< orphan*/  bss_prio_lock; int /*<<< orphan*/  bss_prio_head; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 size_t MAX_NUM_TID ; 
 int /*<<< orphan*/  idr_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int mwifiex_init_lock_list(struct mwifiex_adapter *adapter)
{
	struct mwifiex_private *priv;
	s32 i, j;

	spin_lock_init(&adapter->int_lock);
	spin_lock_init(&adapter->main_proc_lock);
	spin_lock_init(&adapter->mwifiex_cmd_lock);
	spin_lock_init(&adapter->queue_lock);
	for (i = 0; i < adapter->priv_num; i++) {
		if (adapter->priv[i]) {
			priv = adapter->priv[i];
			spin_lock_init(&priv->wmm.ra_list_spinlock);
			spin_lock_init(&priv->curr_bcn_buf_lock);
			spin_lock_init(&priv->sta_list_spinlock);
			spin_lock_init(&priv->auto_tdls_lock);
		}
	}

	/* Initialize cmd_free_q */
	INIT_LIST_HEAD(&adapter->cmd_free_q);
	/* Initialize cmd_pending_q */
	INIT_LIST_HEAD(&adapter->cmd_pending_q);
	/* Initialize scan_pending_q */
	INIT_LIST_HEAD(&adapter->scan_pending_q);

	spin_lock_init(&adapter->cmd_free_q_lock);
	spin_lock_init(&adapter->cmd_pending_q_lock);
	spin_lock_init(&adapter->scan_pending_q_lock);
	spin_lock_init(&adapter->rx_proc_lock);

	skb_queue_head_init(&adapter->rx_data_q);
	skb_queue_head_init(&adapter->tx_data_q);

	for (i = 0; i < adapter->priv_num; ++i) {
		INIT_LIST_HEAD(&adapter->bss_prio_tbl[i].bss_prio_head);
		spin_lock_init(&adapter->bss_prio_tbl[i].bss_prio_lock);
	}

	for (i = 0; i < adapter->priv_num; i++) {
		if (!adapter->priv[i])
			continue;
		priv = adapter->priv[i];
		for (j = 0; j < MAX_NUM_TID; ++j)
			INIT_LIST_HEAD(&priv->wmm.tid_tbl_ptr[j].ra_list);
		INIT_LIST_HEAD(&priv->tx_ba_stream_tbl_ptr);
		INIT_LIST_HEAD(&priv->rx_reorder_tbl_ptr);
		INIT_LIST_HEAD(&priv->sta_list);
		INIT_LIST_HEAD(&priv->auto_tdls_list);
		skb_queue_head_init(&priv->tdls_txq);
		skb_queue_head_init(&priv->bypass_txq);

		spin_lock_init(&priv->tx_ba_stream_tbl_lock);
		spin_lock_init(&priv->rx_reorder_tbl_lock);

		spin_lock_init(&priv->ack_status_lock);
		idr_init(&priv->ack_status_frames);
	}

	return 0;
}
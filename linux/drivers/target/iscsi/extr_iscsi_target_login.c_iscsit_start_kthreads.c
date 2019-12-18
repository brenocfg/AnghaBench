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
struct iscsi_conn {scalar_t__ bitmap_id; int tx_thread_active; int rx_thread_active; void* tx_thread; void* rx_thread; } ;
struct TYPE_2__ {int /*<<< orphan*/  ts_bitmap_lock; int /*<<< orphan*/  ts_bitmap; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  ISCSIT_BITMAP_BITS ; 
 int /*<<< orphan*/  ISCSI_RX_THREAD_NAME ; 
 int /*<<< orphan*/  ISCSI_TX_THREAD_NAME ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  SIGINT ; 
 scalar_t__ bitmap_find_free_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bitmap_release_region (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_order (int) ; 
 int /*<<< orphan*/  iscsi_target_rx_thread ; 
 int /*<<< orphan*/  iscsi_target_tx_thread ; 
 TYPE_1__* iscsit_global ; 
 void* kthread_run (int /*<<< orphan*/ ,struct iscsi_conn*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kthread_stop (void*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  send_sig (int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int iscsit_start_kthreads(struct iscsi_conn *conn)
{
	int ret = 0;

	spin_lock(&iscsit_global->ts_bitmap_lock);
	conn->bitmap_id = bitmap_find_free_region(iscsit_global->ts_bitmap,
					ISCSIT_BITMAP_BITS, get_order(1));
	spin_unlock(&iscsit_global->ts_bitmap_lock);

	if (conn->bitmap_id < 0) {
		pr_err("bitmap_find_free_region() failed for"
		       " iscsit_start_kthreads()\n");
		return -ENOMEM;
	}

	conn->tx_thread = kthread_run(iscsi_target_tx_thread, conn,
				      "%s", ISCSI_TX_THREAD_NAME);
	if (IS_ERR(conn->tx_thread)) {
		pr_err("Unable to start iscsi_target_tx_thread\n");
		ret = PTR_ERR(conn->tx_thread);
		goto out_bitmap;
	}
	conn->tx_thread_active = true;

	conn->rx_thread = kthread_run(iscsi_target_rx_thread, conn,
				      "%s", ISCSI_RX_THREAD_NAME);
	if (IS_ERR(conn->rx_thread)) {
		pr_err("Unable to start iscsi_target_rx_thread\n");
		ret = PTR_ERR(conn->rx_thread);
		goto out_tx;
	}
	conn->rx_thread_active = true;

	return 0;
out_tx:
	send_sig(SIGINT, conn->tx_thread, 1);
	kthread_stop(conn->tx_thread);
	conn->tx_thread_active = false;
out_bitmap:
	spin_lock(&iscsit_global->ts_bitmap_lock);
	bitmap_release_region(iscsit_global->ts_bitmap, conn->bitmap_id,
			      get_order(1));
	spin_unlock(&iscsit_global->ts_bitmap_lock);
	return ret;
}
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
struct TYPE_5__ {int /*<<< orphan*/  used; } ;
struct TYPE_4__ {int /*<<< orphan*/  id; } ;
struct be_tx_obj {TYPE_2__ q; TYPE_1__ cq; } ;
struct be_tx_compl_info {int /*<<< orphan*/  end_index; } ;
struct be_adapter {int /*<<< orphan*/  netdev; } ;
struct TYPE_6__ {int tx_compl; int /*<<< orphan*/  sync_compl; } ;

/* Variables and functions */
 scalar_t__ __netif_subqueue_stopped (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  atomic_sub (int,int /*<<< orphan*/ *) ; 
 scalar_t__ be_can_txq_wake (struct be_tx_obj*) ; 
 int /*<<< orphan*/  be_cq_notify (struct be_adapter*,int /*<<< orphan*/ ,int,int) ; 
 struct be_tx_compl_info* be_tx_compl_get (struct be_adapter*,struct be_tx_obj*) ; 
 scalar_t__ be_tx_compl_process (struct be_adapter*,struct be_tx_obj*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_wake_subqueue (int /*<<< orphan*/ ,int) ; 
 TYPE_3__* tx_stats (struct be_tx_obj*) ; 
 int /*<<< orphan*/  u64_stats_update_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  u64_stats_update_end (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void be_process_tx(struct be_adapter *adapter, struct be_tx_obj *txo,
			  int idx)
{
	int num_wrbs = 0, work_done = 0;
	struct be_tx_compl_info *txcp;

	while ((txcp = be_tx_compl_get(adapter, txo))) {
		num_wrbs += be_tx_compl_process(adapter, txo, txcp->end_index);
		work_done++;
	}

	if (work_done) {
		be_cq_notify(adapter, txo->cq.id, true, work_done);
		atomic_sub(num_wrbs, &txo->q.used);

		/* As Tx wrbs have been freed up, wake up netdev queue
		 * if it was stopped due to lack of tx wrbs.  */
		if (__netif_subqueue_stopped(adapter->netdev, idx) &&
		    be_can_txq_wake(txo)) {
			netif_wake_subqueue(adapter->netdev, idx);
		}

		u64_stats_update_begin(&tx_stats(txo)->sync_compl);
		tx_stats(txo)->tx_compl += work_done;
		u64_stats_update_end(&tx_stats(txo)->sync_compl);
	}
}
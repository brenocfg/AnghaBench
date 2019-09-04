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
struct be_queue_info {int /*<<< orphan*/  id; } ;
struct be_rx_obj {struct be_adapter* adapter; struct be_queue_info cq; } ;
struct be_rx_compl_info {scalar_t__ num_rcvd; } ;
struct be_adapter {TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BE_ERROR_HW ; 
 scalar_t__ be_check_error (struct be_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be_cq_notify (struct be_adapter*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  be_rx_compl_discard (struct be_rx_obj*,struct be_rx_compl_info*) ; 
 struct be_rx_compl_info* be_rx_compl_get (struct be_rx_obj*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ lancer_chip (struct be_adapter*) ; 
 int /*<<< orphan*/  mdelay (int) ; 

__attribute__((used)) static void be_rx_cq_clean(struct be_rx_obj *rxo)
{
	struct be_queue_info *rx_cq = &rxo->cq;
	struct be_rx_compl_info *rxcp;
	struct be_adapter *adapter = rxo->adapter;
	int flush_wait = 0;

	/* Consume pending rx completions.
	 * Wait for the flush completion (identified by zero num_rcvd)
	 * to arrive. Notify CQ even when there are no more CQ entries
	 * for HW to flush partially coalesced CQ entries.
	 * In Lancer, there is no need to wait for flush compl.
	 */
	for (;;) {
		rxcp = be_rx_compl_get(rxo);
		if (!rxcp) {
			if (lancer_chip(adapter))
				break;

			if (flush_wait++ > 50 ||
			    be_check_error(adapter,
					   BE_ERROR_HW)) {
				dev_warn(&adapter->pdev->dev,
					 "did not receive flush compl\n");
				break;
			}
			be_cq_notify(adapter, rx_cq->id, true, 0);
			mdelay(1);
		} else {
			be_rx_compl_discard(rxo, rxcp);
			be_cq_notify(adapter, rx_cq->id, false, 1);
			if (rxcp->num_rcvd == 0)
				break;
		}
	}

	/* After cleanup, leave the CQ in unarmed state */
	be_cq_notify(adapter, rx_cq->id, false, 0);
}
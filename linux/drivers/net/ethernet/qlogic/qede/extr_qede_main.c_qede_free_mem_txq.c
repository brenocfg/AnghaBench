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
struct TYPE_4__ {int /*<<< orphan*/  skbs; int /*<<< orphan*/  xdp; } ;
struct qede_tx_queue {int /*<<< orphan*/  tx_pbl; TYPE_1__ sw_tx_ring; scalar_t__ is_xdp; } ;
struct qede_dev {int /*<<< orphan*/  cdev; TYPE_3__* ops; } ;
struct TYPE_6__ {TYPE_2__* common; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* chain_free ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void qede_free_mem_txq(struct qede_dev *edev, struct qede_tx_queue *txq)
{
	/* Free the parallel SW ring */
	if (txq->is_xdp)
		kfree(txq->sw_tx_ring.xdp);
	else
		kfree(txq->sw_tx_ring.skbs);

	/* Free the real RQ ring used by FW */
	edev->ops->common->chain_free(edev->cdev, &txq->tx_pbl);
}
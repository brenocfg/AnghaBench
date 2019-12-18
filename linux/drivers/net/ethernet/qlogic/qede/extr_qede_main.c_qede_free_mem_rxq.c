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
struct qede_rx_queue {int /*<<< orphan*/  rx_comp_ring; int /*<<< orphan*/  rx_bd_ring; int /*<<< orphan*/  sw_rx_ring; } ;
struct qede_dev {int /*<<< orphan*/  cdev; TYPE_2__* ops; } ;
struct TYPE_4__ {TYPE_1__* common; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* chain_free ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qede_free_rx_buffers (struct qede_dev*,struct qede_rx_queue*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void qede_free_mem_rxq(struct qede_dev *edev, struct qede_rx_queue *rxq)
{
	/* Free rx buffers */
	qede_free_rx_buffers(edev, rxq);

	/* Free the parallel SW ring */
	kfree(rxq->sw_rx_ring);

	/* Free the real RQ ring used by FW */
	edev->ops->common->chain_free(edev->cdev, &rxq->rx_bd_ring);
	edev->ops->common->chain_free(edev->cdev, &rxq->rx_comp_ring);
}
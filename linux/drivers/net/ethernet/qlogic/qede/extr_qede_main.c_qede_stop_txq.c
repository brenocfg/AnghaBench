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
struct qede_tx_queue {int /*<<< orphan*/  handle; int /*<<< orphan*/  tx_db; int /*<<< orphan*/  doorbell_addr; } ;
struct qede_dev {int /*<<< orphan*/  cdev; TYPE_2__* ops; } ;
struct TYPE_4__ {int (* q_tx_stop ) (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ;TYPE_1__* common; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* db_recovery_del ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int stub2 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qede_stop_txq(struct qede_dev *edev,
			 struct qede_tx_queue *txq, int rss_id)
{
	/* delete doorbell from doorbell recovery mechanism */
	edev->ops->common->db_recovery_del(edev->cdev, txq->doorbell_addr,
					   &txq->tx_db);

	return edev->ops->q_tx_stop(edev->cdev, rss_id, txq->handle);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  pbl; } ;
struct TYPE_6__ {int /*<<< orphan*/  pbl; } ;
struct qedr_qp {int /*<<< orphan*/  rqe_wr_id; TYPE_1__ rq; int /*<<< orphan*/  wqe_wr_id; TYPE_2__ sq; } ;
struct qedr_dev {int /*<<< orphan*/  cdev; TYPE_4__* ops; } ;
struct TYPE_8__ {TYPE_3__* common; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* chain_free ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void qedr_cleanup_kernel(struct qedr_dev *dev, struct qedr_qp *qp)
{
	dev->ops->common->chain_free(dev->cdev, &qp->sq.pbl);
	kfree(qp->wqe_wr_id);

	dev->ops->common->chain_free(dev->cdev, &qp->rq.pbl);
	kfree(qp->rqe_wr_id);
}
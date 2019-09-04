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
struct TYPE_4__ {scalar_t__ msix_cnt; } ;
struct qedr_dev {TYPE_2__ int_info; int /*<<< orphan*/  cdev; TYPE_1__* ops; int /*<<< orphan*/  num_cnq; } ;
struct TYPE_3__ {int (* rdma_set_rdma_int ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int (* rdma_get_rdma_int ) (int /*<<< orphan*/ ,TYPE_2__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DP_DEBUG (struct qedr_dev*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  QEDR_MSG_INIT ; 
 int qedr_req_msix_irqs (struct qedr_dev*) ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub2 (int /*<<< orphan*/ ,TYPE_2__*) ; 

__attribute__((used)) static int qedr_setup_irqs(struct qedr_dev *dev)
{
	int rc;

	DP_DEBUG(dev, QEDR_MSG_INIT, "qedr_setup_irqs\n");

	/* Learn Interrupt configuration */
	rc = dev->ops->rdma_set_rdma_int(dev->cdev, dev->num_cnq);
	if (rc < 0)
		return rc;

	rc = dev->ops->rdma_get_rdma_int(dev->cdev, &dev->int_info);
	if (rc) {
		DP_DEBUG(dev, QEDR_MSG_INIT, "get_rdma_int failed\n");
		return rc;
	}

	if (dev->int_info.msix_cnt) {
		DP_DEBUG(dev, QEDR_MSG_INIT, "rdma msix_cnt = %d\n",
			 dev->int_info.msix_cnt);
		rc = qedr_req_msix_irqs(dev);
		if (rc)
			return rc;
	}

	DP_DEBUG(dev, QEDR_MSG_INIT, "qedr_setup_irqs succeeded\n");

	return 0;
}
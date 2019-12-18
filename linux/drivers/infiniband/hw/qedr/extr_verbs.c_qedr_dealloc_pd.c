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
struct qedr_pd {int /*<<< orphan*/  pd_id; } ;
struct qedr_dev {int /*<<< orphan*/  rdma_ctx; TYPE_1__* ops; } ;
struct ib_udata {int dummy; } ;
struct ib_pd {int /*<<< orphan*/  device; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* rdma_dealloc_pd ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DP_DEBUG (struct qedr_dev*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QEDR_MSG_INIT ; 
 struct qedr_dev* get_qedr_dev (int /*<<< orphan*/ ) ; 
 struct qedr_pd* get_qedr_pd (struct ib_pd*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void qedr_dealloc_pd(struct ib_pd *ibpd, struct ib_udata *udata)
{
	struct qedr_dev *dev = get_qedr_dev(ibpd->device);
	struct qedr_pd *pd = get_qedr_pd(ibpd);

	DP_DEBUG(dev, QEDR_MSG_INIT, "Deallocating PD %d\n", pd->pd_id);
	dev->ops->rdma_dealloc_pd(dev->rdma_ctx, pd->pd_id);
}
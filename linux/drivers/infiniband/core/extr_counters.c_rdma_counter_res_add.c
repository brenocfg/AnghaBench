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
struct rdma_counter {int /*<<< orphan*/  res; } ;
struct TYPE_2__ {int /*<<< orphan*/  task; int /*<<< orphan*/  kern_name; } ;
struct ib_qp {TYPE_1__ res; } ;

/* Variables and functions */
 scalar_t__ rdma_is_kernel_res (TYPE_1__*) ; 
 int /*<<< orphan*/  rdma_restrack_attach_task (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdma_restrack_kadd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rdma_restrack_set_task (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdma_restrack_uadd (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rdma_counter_res_add(struct rdma_counter *counter,
				 struct ib_qp *qp)
{
	if (rdma_is_kernel_res(&qp->res)) {
		rdma_restrack_set_task(&counter->res, qp->res.kern_name);
		rdma_restrack_kadd(&counter->res);
	} else {
		rdma_restrack_attach_task(&counter->res, qp->res.task);
		rdma_restrack_uadd(&counter->res);
	}
}
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
struct TYPE_5__ {int /*<<< orphan*/  task; } ;
struct auto_mode_param {scalar_t__ qp_type; } ;
struct TYPE_4__ {struct auto_mode_param param; } ;
struct rdma_counter {TYPE_2__ res; TYPE_1__ mode; } ;
struct TYPE_6__ {int /*<<< orphan*/  task; } ;
struct ib_qp {scalar_t__ qp_type; TYPE_3__ res; } ;
typedef  enum rdma_nl_counter_mask { ____Placeholder_rdma_nl_counter_mask } rdma_nl_counter_mask ;

/* Variables and functions */
 int RDMA_COUNTER_MASK_QP_TYPE ; 
 int /*<<< orphan*/  rdma_is_visible_in_pid_ns (TYPE_3__*) ; 
 scalar_t__ task_pid_nr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool auto_mode_match(struct ib_qp *qp, struct rdma_counter *counter,
			    enum rdma_nl_counter_mask auto_mask)
{
	struct auto_mode_param *param = &counter->mode.param;
	bool match = true;

	if (!rdma_is_visible_in_pid_ns(&qp->res))
		return false;

	/* Ensure that counter belongs to the right PID */
	if (task_pid_nr(counter->res.task) != task_pid_nr(qp->res.task))
		return false;

	if (auto_mask & RDMA_COUNTER_MASK_QP_TYPE)
		match &= (param->qp_type == qp->qp_type);

	return match;
}
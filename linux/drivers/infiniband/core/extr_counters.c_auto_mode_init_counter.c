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
struct auto_mode_param {int /*<<< orphan*/  qp_type; } ;
struct TYPE_2__ {int mask; int /*<<< orphan*/  mode; struct auto_mode_param param; } ;
struct rdma_counter {TYPE_1__ mode; } ;
struct ib_qp {int /*<<< orphan*/  qp_type; } ;
typedef  enum rdma_nl_counter_mask { ____Placeholder_rdma_nl_counter_mask } rdma_nl_counter_mask ;

/* Variables and functions */
 int RDMA_COUNTER_MASK_QP_TYPE ; 
 int /*<<< orphan*/  RDMA_COUNTER_MODE_AUTO ; 

__attribute__((used)) static void auto_mode_init_counter(struct rdma_counter *counter,
				   const struct ib_qp *qp,
				   enum rdma_nl_counter_mask new_mask)
{
	struct auto_mode_param *param = &counter->mode.param;

	counter->mode.mode = RDMA_COUNTER_MODE_AUTO;
	counter->mode.mask = new_mask;

	if (new_mask & RDMA_COUNTER_MASK_QP_TYPE)
		param->qp_type = qp->qp_type;
}
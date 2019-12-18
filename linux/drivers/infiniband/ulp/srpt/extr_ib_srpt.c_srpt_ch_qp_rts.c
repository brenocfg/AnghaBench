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
struct TYPE_2__ {int /*<<< orphan*/  cm_id; } ;
struct srpt_rdma_ch {TYPE_1__ ib_cm; } ;
struct ib_qp_attr {int max_rd_atomic; int /*<<< orphan*/  qp_state; } ;
struct ib_qp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_QPS_RTS ; 
 int ib_cm_init_qp_attr (int /*<<< orphan*/ ,struct ib_qp_attr*,int*) ; 
 int ib_modify_qp (struct ib_qp*,struct ib_qp_attr*,int) ; 

__attribute__((used)) static int srpt_ch_qp_rts(struct srpt_rdma_ch *ch, struct ib_qp *qp)
{
	struct ib_qp_attr qp_attr;
	int attr_mask;
	int ret;

	qp_attr.qp_state = IB_QPS_RTS;
	ret = ib_cm_init_qp_attr(ch->ib_cm.cm_id, &qp_attr, &attr_mask);
	if (ret)
		goto out;

	qp_attr.max_rd_atomic = 4;

	ret = ib_modify_qp(qp, &qp_attr, attr_mask);

out:
	return ret;
}
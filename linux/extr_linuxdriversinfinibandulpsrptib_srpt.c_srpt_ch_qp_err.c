#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct srpt_rdma_ch {int /*<<< orphan*/  qp; } ;
struct ib_qp_attr {int /*<<< orphan*/  qp_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_QPS_ERR ; 
 int /*<<< orphan*/  IB_QP_STATE ; 
 int ib_modify_qp (int /*<<< orphan*/ ,struct ib_qp_attr*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int srpt_ch_qp_err(struct srpt_rdma_ch *ch)
{
	struct ib_qp_attr qp_attr;

	qp_attr.qp_state = IB_QPS_ERR;
	return ib_modify_qp(ch->qp, &qp_attr, IB_QP_STATE);
}
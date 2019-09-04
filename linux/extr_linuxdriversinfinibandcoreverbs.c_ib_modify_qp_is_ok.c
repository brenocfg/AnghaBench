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
typedef  enum rdma_link_layer { ____Placeholder_rdma_link_layer } rdma_link_layer ;
typedef  enum ib_qp_type { ____Placeholder_ib_qp_type } ib_qp_type ;
typedef  enum ib_qp_state { ____Placeholder_ib_qp_state } ib_qp_state ;
typedef  enum ib_qp_attr_mask { ____Placeholder_ib_qp_attr_mask } ib_qp_attr_mask ;
struct TYPE_2__ {int* req_param; int* opt_param; int /*<<< orphan*/  valid; } ;

/* Variables and functions */
 int IB_QPS_RTR ; 
 int IB_QPS_RTS ; 
 int IB_QPS_SQD ; 
 int IB_QPS_SQE ; 
 int IB_QP_CUR_STATE ; 
 int IB_QP_STATE ; 
 TYPE_1__** qp_state_table ; 

bool ib_modify_qp_is_ok(enum ib_qp_state cur_state, enum ib_qp_state next_state,
			enum ib_qp_type type, enum ib_qp_attr_mask mask,
			enum rdma_link_layer ll)
{
	enum ib_qp_attr_mask req_param, opt_param;

	if (mask & IB_QP_CUR_STATE  &&
	    cur_state != IB_QPS_RTR && cur_state != IB_QPS_RTS &&
	    cur_state != IB_QPS_SQD && cur_state != IB_QPS_SQE)
		return false;

	if (!qp_state_table[cur_state][next_state].valid)
		return false;

	req_param = qp_state_table[cur_state][next_state].req_param[type];
	opt_param = qp_state_table[cur_state][next_state].opt_param[type];

	if ((mask & req_param) != req_param)
		return false;

	if (mask & ~(req_param | opt_param | IB_QP_STATE))
		return false;

	return true;
}
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
typedef  enum qed_roce_qp_state { ____Placeholder_qed_roce_qp_state } qed_roce_qp_state ;
typedef  enum ib_qp_state { ____Placeholder_ib_qp_state } ib_qp_state ;

/* Variables and functions */
#define  IB_QPS_ERR 133 
#define  IB_QPS_INIT 132 
#define  IB_QPS_RESET 131 
#define  IB_QPS_RTR 130 
#define  IB_QPS_RTS 129 
#define  IB_QPS_SQD 128 
 int QED_ROCE_QP_STATE_ERR ; 
 int QED_ROCE_QP_STATE_INIT ; 
 int QED_ROCE_QP_STATE_RESET ; 
 int QED_ROCE_QP_STATE_RTR ; 
 int QED_ROCE_QP_STATE_RTS ; 
 int QED_ROCE_QP_STATE_SQD ; 

__attribute__((used)) static enum qed_roce_qp_state qedr_get_state_from_ibqp(
					enum ib_qp_state qp_state)
{
	switch (qp_state) {
	case IB_QPS_RESET:
		return QED_ROCE_QP_STATE_RESET;
	case IB_QPS_INIT:
		return QED_ROCE_QP_STATE_INIT;
	case IB_QPS_RTR:
		return QED_ROCE_QP_STATE_RTR;
	case IB_QPS_RTS:
		return QED_ROCE_QP_STATE_RTS;
	case IB_QPS_SQD:
		return QED_ROCE_QP_STATE_SQD;
	case IB_QPS_ERR:
		return QED_ROCE_QP_STATE_ERR;
	default:
		return QED_ROCE_QP_STATE_ERR;
	}
}
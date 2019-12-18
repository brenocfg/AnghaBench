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
typedef  enum ib_qp_state { ____Placeholder_ib_qp_state } ib_qp_state ;
typedef  enum hns_roce_qp_state { ____Placeholder_hns_roce_qp_state } hns_roce_qp_state ;

/* Variables and functions */
 int HNS_ROCE_QP_NUM_STATE ; 
 int HNS_ROCE_QP_STATE_ERR ; 
 int HNS_ROCE_QP_STATE_INIT ; 
 int HNS_ROCE_QP_STATE_RST ; 
 int HNS_ROCE_QP_STATE_RTR ; 
 int HNS_ROCE_QP_STATE_RTS ; 
 int HNS_ROCE_QP_STATE_SQD ; 
#define  IB_QPS_ERR 133 
#define  IB_QPS_INIT 132 
#define  IB_QPS_RESET 131 
#define  IB_QPS_RTR 130 
#define  IB_QPS_RTS 129 
#define  IB_QPS_SQD 128 

enum hns_roce_qp_state to_hns_roce_state(enum ib_qp_state state)
{
	switch (state) {
	case IB_QPS_RESET:
		return HNS_ROCE_QP_STATE_RST;
	case IB_QPS_INIT:
		return HNS_ROCE_QP_STATE_INIT;
	case IB_QPS_RTR:
		return HNS_ROCE_QP_STATE_RTR;
	case IB_QPS_RTS:
		return HNS_ROCE_QP_STATE_RTS;
	case IB_QPS_SQD:
		return HNS_ROCE_QP_STATE_SQD;
	case IB_QPS_ERR:
		return HNS_ROCE_QP_STATE_ERR;
	default:
		return HNS_ROCE_QP_NUM_STATE;
	}
}
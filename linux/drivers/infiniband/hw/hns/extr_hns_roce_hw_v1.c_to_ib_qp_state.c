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
#define  HNS_ROCE_QP_STATE_ERR 133 
#define  HNS_ROCE_QP_STATE_INIT 132 
#define  HNS_ROCE_QP_STATE_RST 131 
#define  HNS_ROCE_QP_STATE_RTR 130 
#define  HNS_ROCE_QP_STATE_RTS 129 
#define  HNS_ROCE_QP_STATE_SQD 128 
 int IB_QPS_ERR ; 
 int IB_QPS_INIT ; 
 int IB_QPS_RESET ; 
 int IB_QPS_RTR ; 
 int IB_QPS_RTS ; 
 int IB_QPS_SQD ; 

__attribute__((used)) static enum ib_qp_state to_ib_qp_state(enum hns_roce_qp_state state)
{
	switch (state) {
	case HNS_ROCE_QP_STATE_RST:
		return IB_QPS_RESET;
	case HNS_ROCE_QP_STATE_INIT:
		return IB_QPS_INIT;
	case HNS_ROCE_QP_STATE_RTR:
		return IB_QPS_RTR;
	case HNS_ROCE_QP_STATE_RTS:
		return IB_QPS_RTS;
	case HNS_ROCE_QP_STATE_SQD:
		return IB_QPS_SQD;
	case HNS_ROCE_QP_STATE_ERR:
		return IB_QPS_ERR;
	default:
		return IB_QPS_ERR;
	}
}
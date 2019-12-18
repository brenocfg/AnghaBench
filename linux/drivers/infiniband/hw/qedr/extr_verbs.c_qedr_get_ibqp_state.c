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
 int IB_QPS_ERR ; 
 int IB_QPS_INIT ; 
 int IB_QPS_RESET ; 
 int IB_QPS_RTR ; 
 int IB_QPS_RTS ; 
 int IB_QPS_SQD ; 
 int IB_QPS_SQE ; 
#define  QED_ROCE_QP_STATE_ERR 134 
#define  QED_ROCE_QP_STATE_INIT 133 
#define  QED_ROCE_QP_STATE_RESET 132 
#define  QED_ROCE_QP_STATE_RTR 131 
#define  QED_ROCE_QP_STATE_RTS 130 
#define  QED_ROCE_QP_STATE_SQD 129 
#define  QED_ROCE_QP_STATE_SQE 128 

__attribute__((used)) static enum ib_qp_state qedr_get_ibqp_state(enum qed_roce_qp_state qp_state)
{
	switch (qp_state) {
	case QED_ROCE_QP_STATE_RESET:
		return IB_QPS_RESET;
	case QED_ROCE_QP_STATE_INIT:
		return IB_QPS_INIT;
	case QED_ROCE_QP_STATE_RTR:
		return IB_QPS_RTR;
	case QED_ROCE_QP_STATE_RTS:
		return IB_QPS_RTS;
	case QED_ROCE_QP_STATE_SQD:
		return IB_QPS_SQD;
	case QED_ROCE_QP_STATE_ERR:
		return IB_QPS_ERR;
	case QED_ROCE_QP_STATE_SQE:
		return IB_QPS_SQE;
	}
	return IB_QPS_ERR;
}
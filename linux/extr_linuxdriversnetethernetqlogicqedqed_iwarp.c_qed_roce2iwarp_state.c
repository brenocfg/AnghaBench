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
typedef  enum qed_iwarp_qp_state { ____Placeholder_qed_iwarp_qp_state } qed_iwarp_qp_state ;

/* Variables and functions */
 int QED_IWARP_QP_STATE_CLOSING ; 
 int QED_IWARP_QP_STATE_ERROR ; 
 int QED_IWARP_QP_STATE_IDLE ; 
 int QED_IWARP_QP_STATE_RTS ; 
 int QED_IWARP_QP_STATE_TERMINATE ; 
#define  QED_ROCE_QP_STATE_ERR 134 
#define  QED_ROCE_QP_STATE_INIT 133 
#define  QED_ROCE_QP_STATE_RESET 132 
#define  QED_ROCE_QP_STATE_RTR 131 
#define  QED_ROCE_QP_STATE_RTS 130 
#define  QED_ROCE_QP_STATE_SQD 129 
#define  QED_ROCE_QP_STATE_SQE 128 

enum qed_iwarp_qp_state qed_roce2iwarp_state(enum qed_roce_qp_state state)
{
	switch (state) {
	case QED_ROCE_QP_STATE_RESET:
	case QED_ROCE_QP_STATE_INIT:
	case QED_ROCE_QP_STATE_RTR:
		return QED_IWARP_QP_STATE_IDLE;
	case QED_ROCE_QP_STATE_RTS:
		return QED_IWARP_QP_STATE_RTS;
	case QED_ROCE_QP_STATE_SQD:
		return QED_IWARP_QP_STATE_CLOSING;
	case QED_ROCE_QP_STATE_ERR:
		return QED_IWARP_QP_STATE_ERROR;
	case QED_ROCE_QP_STATE_SQE:
		return QED_IWARP_QP_STATE_TERMINATE;
	default:
		return QED_IWARP_QP_STATE_ERROR;
	}
}
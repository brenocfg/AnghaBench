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
#define  QED_IWARP_QP_STATE_CLOSING 132 
#define  QED_IWARP_QP_STATE_ERROR 131 
#define  QED_IWARP_QP_STATE_IDLE 130 
#define  QED_IWARP_QP_STATE_RTS 129 
#define  QED_IWARP_QP_STATE_TERMINATE 128 
 int QED_ROCE_QP_STATE_ERR ; 
 int QED_ROCE_QP_STATE_INIT ; 
 int QED_ROCE_QP_STATE_RTS ; 
 int QED_ROCE_QP_STATE_SQD ; 
 int QED_ROCE_QP_STATE_SQE ; 

__attribute__((used)) static enum qed_roce_qp_state
qed_iwarp2roce_state(enum qed_iwarp_qp_state state)
{
	switch (state) {
	case QED_IWARP_QP_STATE_IDLE:
		return QED_ROCE_QP_STATE_INIT;
	case QED_IWARP_QP_STATE_RTS:
		return QED_ROCE_QP_STATE_RTS;
	case QED_IWARP_QP_STATE_TERMINATE:
		return QED_ROCE_QP_STATE_SQE;
	case QED_IWARP_QP_STATE_CLOSING:
		return QED_ROCE_QP_STATE_SQD;
	case QED_IWARP_QP_STATE_ERROR:
		return QED_ROCE_QP_STATE_ERR;
	default:
		return QED_ROCE_QP_STATE_ERR;
	}
}
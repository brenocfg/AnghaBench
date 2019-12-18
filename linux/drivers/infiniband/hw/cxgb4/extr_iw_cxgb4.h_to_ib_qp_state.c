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

/* Variables and functions */
#define  C4IW_QP_STATE_CLOSING 132 
#define  C4IW_QP_STATE_ERROR 131 
#define  C4IW_QP_STATE_IDLE 130 
#define  C4IW_QP_STATE_RTS 129 
#define  C4IW_QP_STATE_TERMINATE 128 
 int IB_QPS_ERR ; 
 int IB_QPS_INIT ; 
 int IB_QPS_RTS ; 
 int IB_QPS_SQD ; 
 int IB_QPS_SQE ; 

__attribute__((used)) static inline int to_ib_qp_state(int c4iw_qp_state)
{
	switch (c4iw_qp_state) {
	case C4IW_QP_STATE_IDLE:
		return IB_QPS_INIT;
	case C4IW_QP_STATE_RTS:
		return IB_QPS_RTS;
	case C4IW_QP_STATE_CLOSING:
		return IB_QPS_SQD;
	case C4IW_QP_STATE_TERMINATE:
		return IB_QPS_SQE;
	case C4IW_QP_STATE_ERROR:
		return IB_QPS_ERR;
	}
	return IB_QPS_ERR;
}
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

/* Variables and functions */
#define  IB_QPS_ERR 134 
#define  IB_QPS_INIT 133 
#define  IB_QPS_RESET 132 
#define  IB_QPS_RTR 131 
#define  IB_QPS_RTS 130 
#define  IB_QPS_SQD 129 
#define  IB_QPS_SQE 128 
 int MTHCA_QP_STATE_ERR ; 
 int MTHCA_QP_STATE_INIT ; 
 int MTHCA_QP_STATE_RST ; 
 int MTHCA_QP_STATE_RTR ; 
 int MTHCA_QP_STATE_RTS ; 
 int MTHCA_QP_STATE_SQD ; 
 int MTHCA_QP_STATE_SQE ; 

__attribute__((used)) static int to_mthca_state(enum ib_qp_state ib_state)
{
	switch (ib_state) {
	case IB_QPS_RESET: return MTHCA_QP_STATE_RST;
	case IB_QPS_INIT:  return MTHCA_QP_STATE_INIT;
	case IB_QPS_RTR:   return MTHCA_QP_STATE_RTR;
	case IB_QPS_RTS:   return MTHCA_QP_STATE_RTS;
	case IB_QPS_SQD:   return MTHCA_QP_STATE_SQD;
	case IB_QPS_SQE:   return MTHCA_QP_STATE_SQE;
	case IB_QPS_ERR:   return MTHCA_QP_STATE_ERR;
	default:                return -1;
	}
}
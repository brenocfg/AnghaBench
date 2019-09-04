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
typedef  enum ocrdma_qp_state { ____Placeholder_ocrdma_qp_state } ocrdma_qp_state ;
typedef  enum ib_qp_state { ____Placeholder_ib_qp_state } ib_qp_state ;

/* Variables and functions */
 int IB_QPS_ERR ; 
 int IB_QPS_INIT ; 
 int IB_QPS_RESET ; 
 int IB_QPS_RTR ; 
 int IB_QPS_RTS ; 
 int IB_QPS_SQD ; 
 int IB_QPS_SQE ; 
#define  OCRDMA_QPS_ERR 135 
#define  OCRDMA_QPS_INIT 134 
#define  OCRDMA_QPS_RST 133 
#define  OCRDMA_QPS_RTR 132 
#define  OCRDMA_QPS_RTS 131 
#define  OCRDMA_QPS_SQD 130 
#define  OCRDMA_QPS_SQE 129 
#define  OCRDMA_QPS_SQ_DRAINING 128 

enum ib_qp_state get_ibqp_state(enum ocrdma_qp_state qps)
{
	switch (qps) {
	case OCRDMA_QPS_RST:
		return IB_QPS_RESET;
	case OCRDMA_QPS_INIT:
		return IB_QPS_INIT;
	case OCRDMA_QPS_RTR:
		return IB_QPS_RTR;
	case OCRDMA_QPS_RTS:
		return IB_QPS_RTS;
	case OCRDMA_QPS_SQD:
	case OCRDMA_QPS_SQ_DRAINING:
		return IB_QPS_SQD;
	case OCRDMA_QPS_SQE:
		return IB_QPS_SQE;
	case OCRDMA_QPS_ERR:
		return IB_QPS_ERR;
	}
	return IB_QPS_ERR;
}
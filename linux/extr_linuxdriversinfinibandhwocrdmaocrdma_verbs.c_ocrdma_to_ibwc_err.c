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
typedef  int u16 ;
typedef  enum ib_wc_status { ____Placeholder_ib_wc_status } ib_wc_status ;

/* Variables and functions */
 int IB_WC_BAD_RESP_ERR ; 
 int IB_WC_FATAL_ERR ; 
 int IB_WC_GENERAL_ERR ; 
 int IB_WC_INV_EECN_ERR ; 
 int IB_WC_INV_EEC_STATE_ERR ; 
 int IB_WC_LOC_ACCESS_ERR ; 
 int IB_WC_LOC_EEC_OP_ERR ; 
 int IB_WC_LOC_LEN_ERR ; 
 int IB_WC_LOC_PROT_ERR ; 
 int IB_WC_LOC_QP_OP_ERR ; 
 int IB_WC_LOC_RDD_VIOL_ERR ; 
 int IB_WC_MW_BIND_ERR ; 
 int IB_WC_REM_ABORT_ERR ; 
 int IB_WC_REM_ACCESS_ERR ; 
 int IB_WC_REM_INV_RD_REQ_ERR ; 
 int IB_WC_REM_INV_REQ_ERR ; 
 int IB_WC_REM_OP_ERR ; 
 int IB_WC_RESP_TIMEOUT_ERR ; 
 int IB_WC_RETRY_EXC_ERR ; 
 int IB_WC_RNR_RETRY_EXC_ERR ; 
 int IB_WC_WR_FLUSH_ERR ; 
#define  OCRDMA_CQE_BAD_RESP_ERR 148 
#define  OCRDMA_CQE_FATAL_ERR 147 
#define  OCRDMA_CQE_GENERAL_ERR 146 
#define  OCRDMA_CQE_INV_EECN_ERR 145 
#define  OCRDMA_CQE_INV_EEC_STATE_ERR 144 
#define  OCRDMA_CQE_LOC_ACCESS_ERR 143 
#define  OCRDMA_CQE_LOC_EEC_OP_ERR 142 
#define  OCRDMA_CQE_LOC_LEN_ERR 141 
#define  OCRDMA_CQE_LOC_PROT_ERR 140 
#define  OCRDMA_CQE_LOC_QP_OP_ERR 139 
#define  OCRDMA_CQE_LOC_RDD_VIOL_ERR 138 
#define  OCRDMA_CQE_MW_BIND_ERR 137 
#define  OCRDMA_CQE_REM_ABORT_ERR 136 
#define  OCRDMA_CQE_REM_ACCESS_ERR 135 
#define  OCRDMA_CQE_REM_INV_RD_REQ_ERR 134 
#define  OCRDMA_CQE_REM_INV_REQ_ERR 133 
#define  OCRDMA_CQE_REM_OP_ERR 132 
#define  OCRDMA_CQE_RESP_TIMEOUT_ERR 131 
#define  OCRDMA_CQE_RETRY_EXC_ERR 130 
#define  OCRDMA_CQE_RNR_RETRY_EXC_ERR 129 
#define  OCRDMA_CQE_WR_FLUSH_ERR 128 

__attribute__((used)) static enum ib_wc_status ocrdma_to_ibwc_err(u16 status)
{
	enum ib_wc_status ibwc_status;

	switch (status) {
	case OCRDMA_CQE_GENERAL_ERR:
		ibwc_status = IB_WC_GENERAL_ERR;
		break;
	case OCRDMA_CQE_LOC_LEN_ERR:
		ibwc_status = IB_WC_LOC_LEN_ERR;
		break;
	case OCRDMA_CQE_LOC_QP_OP_ERR:
		ibwc_status = IB_WC_LOC_QP_OP_ERR;
		break;
	case OCRDMA_CQE_LOC_EEC_OP_ERR:
		ibwc_status = IB_WC_LOC_EEC_OP_ERR;
		break;
	case OCRDMA_CQE_LOC_PROT_ERR:
		ibwc_status = IB_WC_LOC_PROT_ERR;
		break;
	case OCRDMA_CQE_WR_FLUSH_ERR:
		ibwc_status = IB_WC_WR_FLUSH_ERR;
		break;
	case OCRDMA_CQE_MW_BIND_ERR:
		ibwc_status = IB_WC_MW_BIND_ERR;
		break;
	case OCRDMA_CQE_BAD_RESP_ERR:
		ibwc_status = IB_WC_BAD_RESP_ERR;
		break;
	case OCRDMA_CQE_LOC_ACCESS_ERR:
		ibwc_status = IB_WC_LOC_ACCESS_ERR;
		break;
	case OCRDMA_CQE_REM_INV_REQ_ERR:
		ibwc_status = IB_WC_REM_INV_REQ_ERR;
		break;
	case OCRDMA_CQE_REM_ACCESS_ERR:
		ibwc_status = IB_WC_REM_ACCESS_ERR;
		break;
	case OCRDMA_CQE_REM_OP_ERR:
		ibwc_status = IB_WC_REM_OP_ERR;
		break;
	case OCRDMA_CQE_RETRY_EXC_ERR:
		ibwc_status = IB_WC_RETRY_EXC_ERR;
		break;
	case OCRDMA_CQE_RNR_RETRY_EXC_ERR:
		ibwc_status = IB_WC_RNR_RETRY_EXC_ERR;
		break;
	case OCRDMA_CQE_LOC_RDD_VIOL_ERR:
		ibwc_status = IB_WC_LOC_RDD_VIOL_ERR;
		break;
	case OCRDMA_CQE_REM_INV_RD_REQ_ERR:
		ibwc_status = IB_WC_REM_INV_RD_REQ_ERR;
		break;
	case OCRDMA_CQE_REM_ABORT_ERR:
		ibwc_status = IB_WC_REM_ABORT_ERR;
		break;
	case OCRDMA_CQE_INV_EECN_ERR:
		ibwc_status = IB_WC_INV_EECN_ERR;
		break;
	case OCRDMA_CQE_INV_EEC_STATE_ERR:
		ibwc_status = IB_WC_INV_EEC_STATE_ERR;
		break;
	case OCRDMA_CQE_FATAL_ERR:
		ibwc_status = IB_WC_FATAL_ERR;
		break;
	case OCRDMA_CQE_RESP_TIMEOUT_ERR:
		ibwc_status = IB_WC_RESP_TIMEOUT_ERR;
		break;
	default:
		ibwc_status = IB_WC_GENERAL_ERR;
		break;
	}
	return ibwc_status;
}
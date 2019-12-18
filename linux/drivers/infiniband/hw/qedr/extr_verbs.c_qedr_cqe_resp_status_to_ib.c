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
typedef  int u8 ;

/* Variables and functions */
 int IB_WC_GENERAL_ERR ; 
 int IB_WC_LOC_ACCESS_ERR ; 
 int IB_WC_LOC_LEN_ERR ; 
 int IB_WC_LOC_PROT_ERR ; 
 int IB_WC_LOC_QP_OP_ERR ; 
 int IB_WC_MW_BIND_ERR ; 
 int IB_WC_REM_INV_RD_REQ_ERR ; 
 int IB_WC_SUCCESS ; 
#define  RDMA_CQE_RESP_STS_LOCAL_ACCESS_ERR 134 
#define  RDMA_CQE_RESP_STS_LOCAL_LENGTH_ERR 133 
#define  RDMA_CQE_RESP_STS_LOCAL_PROTECTION_ERR 132 
#define  RDMA_CQE_RESP_STS_LOCAL_QP_OPERATION_ERR 131 
#define  RDMA_CQE_RESP_STS_MEMORY_MGT_OPERATION_ERR 130 
#define  RDMA_CQE_RESP_STS_OK 129 
#define  RDMA_CQE_RESP_STS_REMOTE_INVALID_REQUEST_ERR 128 

__attribute__((used)) static inline int qedr_cqe_resp_status_to_ib(u8 status)
{
	switch (status) {
	case RDMA_CQE_RESP_STS_LOCAL_ACCESS_ERR:
		return IB_WC_LOC_ACCESS_ERR;
	case RDMA_CQE_RESP_STS_LOCAL_LENGTH_ERR:
		return IB_WC_LOC_LEN_ERR;
	case RDMA_CQE_RESP_STS_LOCAL_QP_OPERATION_ERR:
		return IB_WC_LOC_QP_OP_ERR;
	case RDMA_CQE_RESP_STS_LOCAL_PROTECTION_ERR:
		return IB_WC_LOC_PROT_ERR;
	case RDMA_CQE_RESP_STS_MEMORY_MGT_OPERATION_ERR:
		return IB_WC_MW_BIND_ERR;
	case RDMA_CQE_RESP_STS_REMOTE_INVALID_REQUEST_ERR:
		return IB_WC_REM_INV_RD_REQ_ERR;
	case RDMA_CQE_RESP_STS_OK:
		return IB_WC_SUCCESS;
	default:
		return IB_WC_GENERAL_ERR;
	}
}
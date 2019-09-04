#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_4__ {char* debugfs_mem; } ;
struct ocrdma_dev {TYPE_3__* cqe_err_stats; TYPE_2__* async_err_stats; TYPE_1__ stats_mem; } ;
struct TYPE_6__ {scalar_t__ counter; } ;
struct TYPE_5__ {scalar_t__ counter; } ;

/* Variables and functions */
 size_t OCRDMA_CQE_BAD_RESP_ERR ; 
 size_t OCRDMA_CQE_FATAL_ERR ; 
 size_t OCRDMA_CQE_GENERAL_ERR ; 
 size_t OCRDMA_CQE_INV_EECN_ERR ; 
 size_t OCRDMA_CQE_INV_EEC_STATE_ERR ; 
 size_t OCRDMA_CQE_LOC_ACCESS_ERR ; 
 size_t OCRDMA_CQE_LOC_EEC_OP_ERR ; 
 size_t OCRDMA_CQE_LOC_LEN_ERR ; 
 size_t OCRDMA_CQE_LOC_PROT_ERR ; 
 size_t OCRDMA_CQE_LOC_QP_OP_ERR ; 
 size_t OCRDMA_CQE_LOC_RDD_VIOL_ERR ; 
 size_t OCRDMA_CQE_MW_BIND_ERR ; 
 size_t OCRDMA_CQE_REM_ABORT_ERR ; 
 size_t OCRDMA_CQE_REM_ACCESS_ERR ; 
 size_t OCRDMA_CQE_REM_INV_RD_REQ_ERR ; 
 size_t OCRDMA_CQE_REM_INV_REQ_ERR ; 
 size_t OCRDMA_CQE_REM_OP_ERR ; 
 size_t OCRDMA_CQE_RESP_TIMEOUT_ERR ; 
 size_t OCRDMA_CQE_RETRY_EXC_ERR ; 
 size_t OCRDMA_CQE_RNR_RETRY_EXC_ERR ; 
 size_t OCRDMA_CQE_WR_FLUSH_ERR ; 
 size_t OCRDMA_CQ_ERROR ; 
 size_t OCRDMA_CQ_OVERRUN_ERROR ; 
 size_t OCRDMA_CQ_QPCAT_ERROR ; 
 size_t OCRDMA_DEVICE_FATAL_EVENT ; 
 int /*<<< orphan*/  OCRDMA_MAX_DBGFS_MEM ; 
 size_t OCRDMA_QP_ACCESS_ERROR ; 
 size_t OCRDMA_QP_COMM_EST_EVENT ; 
 size_t OCRDMA_QP_LAST_WQE_EVENT ; 
 size_t OCRDMA_SQ_DRAINED_EVENT ; 
 size_t OCRDMA_SRQCAT_ERROR ; 
 size_t OCRDMA_SRQ_LIMIT_EVENT ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocrdma_add_stat (char*,char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *ocrdma_driver_dbg_stats(struct ocrdma_dev *dev)
{
	char *stats = dev->stats_mem.debugfs_mem, *pcur;


	memset(stats, 0, (OCRDMA_MAX_DBGFS_MEM));

	pcur = stats;
	pcur += ocrdma_add_stat(stats, pcur, "async_cq_err",
				(u64)(dev->async_err_stats
				[OCRDMA_CQ_ERROR].counter));
	pcur += ocrdma_add_stat(stats, pcur, "async_cq_overrun_err",
				(u64)dev->async_err_stats
				[OCRDMA_CQ_OVERRUN_ERROR].counter);
	pcur += ocrdma_add_stat(stats, pcur, "async_cq_qpcat_err",
				(u64)dev->async_err_stats
				[OCRDMA_CQ_QPCAT_ERROR].counter);
	pcur += ocrdma_add_stat(stats, pcur, "async_qp_access_err",
				(u64)dev->async_err_stats
				[OCRDMA_QP_ACCESS_ERROR].counter);
	pcur += ocrdma_add_stat(stats, pcur, "async_qp_commm_est_evt",
				(u64)dev->async_err_stats
				[OCRDMA_QP_COMM_EST_EVENT].counter);
	pcur += ocrdma_add_stat(stats, pcur, "async_sq_drained_evt",
				(u64)dev->async_err_stats
				[OCRDMA_SQ_DRAINED_EVENT].counter);
	pcur += ocrdma_add_stat(stats, pcur, "async_dev_fatal_evt",
				(u64)dev->async_err_stats
				[OCRDMA_DEVICE_FATAL_EVENT].counter);
	pcur += ocrdma_add_stat(stats, pcur, "async_srqcat_err",
				(u64)dev->async_err_stats
				[OCRDMA_SRQCAT_ERROR].counter);
	pcur += ocrdma_add_stat(stats, pcur, "async_srq_limit_evt",
				(u64)dev->async_err_stats
				[OCRDMA_SRQ_LIMIT_EVENT].counter);
	pcur += ocrdma_add_stat(stats, pcur, "async_qp_last_wqe_evt",
				(u64)dev->async_err_stats
				[OCRDMA_QP_LAST_WQE_EVENT].counter);

	pcur += ocrdma_add_stat(stats, pcur, "cqe_loc_len_err",
				(u64)dev->cqe_err_stats
				[OCRDMA_CQE_LOC_LEN_ERR].counter);
	pcur += ocrdma_add_stat(stats, pcur, "cqe_loc_qp_op_err",
				(u64)dev->cqe_err_stats
				[OCRDMA_CQE_LOC_QP_OP_ERR].counter);
	pcur += ocrdma_add_stat(stats, pcur, "cqe_loc_eec_op_err",
				(u64)dev->cqe_err_stats
				[OCRDMA_CQE_LOC_EEC_OP_ERR].counter);
	pcur += ocrdma_add_stat(stats, pcur, "cqe_loc_prot_err",
				(u64)dev->cqe_err_stats
				[OCRDMA_CQE_LOC_PROT_ERR].counter);
	pcur += ocrdma_add_stat(stats, pcur, "cqe_wr_flush_err",
				(u64)dev->cqe_err_stats
				[OCRDMA_CQE_WR_FLUSH_ERR].counter);
	pcur += ocrdma_add_stat(stats, pcur, "cqe_mw_bind_err",
				(u64)dev->cqe_err_stats
				[OCRDMA_CQE_MW_BIND_ERR].counter);
	pcur += ocrdma_add_stat(stats, pcur, "cqe_bad_resp_err",
				(u64)dev->cqe_err_stats
				[OCRDMA_CQE_BAD_RESP_ERR].counter);
	pcur += ocrdma_add_stat(stats, pcur, "cqe_loc_access_err",
				(u64)dev->cqe_err_stats
				[OCRDMA_CQE_LOC_ACCESS_ERR].counter);
	pcur += ocrdma_add_stat(stats, pcur, "cqe_rem_inv_req_err",
				(u64)dev->cqe_err_stats
				[OCRDMA_CQE_REM_INV_REQ_ERR].counter);
	pcur += ocrdma_add_stat(stats, pcur, "cqe_rem_access_err",
				(u64)dev->cqe_err_stats
				[OCRDMA_CQE_REM_ACCESS_ERR].counter);
	pcur += ocrdma_add_stat(stats, pcur, "cqe_rem_op_err",
				(u64)dev->cqe_err_stats
				[OCRDMA_CQE_REM_OP_ERR].counter);
	pcur += ocrdma_add_stat(stats, pcur, "cqe_retry_exc_err",
				(u64)dev->cqe_err_stats
				[OCRDMA_CQE_RETRY_EXC_ERR].counter);
	pcur += ocrdma_add_stat(stats, pcur, "cqe_rnr_retry_exc_err",
				(u64)dev->cqe_err_stats
				[OCRDMA_CQE_RNR_RETRY_EXC_ERR].counter);
	pcur += ocrdma_add_stat(stats, pcur, "cqe_loc_rdd_viol_err",
				(u64)dev->cqe_err_stats
				[OCRDMA_CQE_LOC_RDD_VIOL_ERR].counter);
	pcur += ocrdma_add_stat(stats, pcur, "cqe_rem_inv_rd_req_err",
				(u64)dev->cqe_err_stats
				[OCRDMA_CQE_REM_INV_RD_REQ_ERR].counter);
	pcur += ocrdma_add_stat(stats, pcur, "cqe_rem_abort_err",
				(u64)dev->cqe_err_stats
				[OCRDMA_CQE_REM_ABORT_ERR].counter);
	pcur += ocrdma_add_stat(stats, pcur, "cqe_inv_eecn_err",
				(u64)dev->cqe_err_stats
				[OCRDMA_CQE_INV_EECN_ERR].counter);
	pcur += ocrdma_add_stat(stats, pcur, "cqe_inv_eec_state_err",
				(u64)dev->cqe_err_stats
				[OCRDMA_CQE_INV_EEC_STATE_ERR].counter);
	pcur += ocrdma_add_stat(stats, pcur, "cqe_fatal_err",
				(u64)dev->cqe_err_stats
				[OCRDMA_CQE_FATAL_ERR].counter);
	pcur += ocrdma_add_stat(stats, pcur, "cqe_resp_timeout_err",
				(u64)dev->cqe_err_stats
				[OCRDMA_CQE_RESP_TIMEOUT_ERR].counter);
	pcur += ocrdma_add_stat(stats, pcur, "cqe_general_err",
				(u64)dev->cqe_err_stats
				[OCRDMA_CQE_GENERAL_ERR].counter);
	return stats;
}
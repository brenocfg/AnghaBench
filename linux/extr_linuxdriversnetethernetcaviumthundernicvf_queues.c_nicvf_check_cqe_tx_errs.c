#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct nicvf {TYPE_1__* drv_stats; } ;
struct cqe_send_t {int send_status; } ;
struct TYPE_2__ {int /*<<< orphan*/  tx_csum_overflow; int /*<<< orphan*/  tx_csum_overlap; int /*<<< orphan*/  tx_mem_fault; int /*<<< orphan*/  tx_tstmp_timeout; int /*<<< orphan*/  tx_tstmp_conflict; int /*<<< orphan*/  tx_data_fault; int /*<<< orphan*/  tx_lock_viol; int /*<<< orphan*/  tx_mem_seq_err; int /*<<< orphan*/  tx_data_seq_err; int /*<<< orphan*/  tx_imm_size_oflow; int /*<<< orphan*/  tx_max_size_exceeded; int /*<<< orphan*/  tx_subdesc_err; int /*<<< orphan*/  tx_hdr_cons_err; int /*<<< orphan*/  tx_desc_fault; } ;

/* Variables and functions */
#define  CQ_TX_ERROP_CK_OFLOW 141 
#define  CQ_TX_ERROP_CK_OVERLAP 140 
#define  CQ_TX_ERROP_DATA_FAULT 139 
#define  CQ_TX_ERROP_DATA_SEQUENCE_ERR 138 
#define  CQ_TX_ERROP_DESC_FAULT 137 
#define  CQ_TX_ERROP_HDR_CONS_ERR 136 
#define  CQ_TX_ERROP_IMM_SIZE_OFLOW 135 
#define  CQ_TX_ERROP_LOCK_VIOL 134 
#define  CQ_TX_ERROP_MAX_SIZE_VIOL 133 
#define  CQ_TX_ERROP_MEM_FAULT 132 
#define  CQ_TX_ERROP_MEM_SEQUENCE_ERR 131 
#define  CQ_TX_ERROP_SUBDC_ERR 130 
#define  CQ_TX_ERROP_TSTMP_CONFLICT 129 
#define  CQ_TX_ERROP_TSTMP_TIMEOUT 128 
 int /*<<< orphan*/  this_cpu_inc (int /*<<< orphan*/ ) ; 

int nicvf_check_cqe_tx_errs(struct nicvf *nic, struct cqe_send_t *cqe_tx)
{
	switch (cqe_tx->send_status) {
	case CQ_TX_ERROP_DESC_FAULT:
		this_cpu_inc(nic->drv_stats->tx_desc_fault);
		break;
	case CQ_TX_ERROP_HDR_CONS_ERR:
		this_cpu_inc(nic->drv_stats->tx_hdr_cons_err);
		break;
	case CQ_TX_ERROP_SUBDC_ERR:
		this_cpu_inc(nic->drv_stats->tx_subdesc_err);
		break;
	case CQ_TX_ERROP_MAX_SIZE_VIOL:
		this_cpu_inc(nic->drv_stats->tx_max_size_exceeded);
		break;
	case CQ_TX_ERROP_IMM_SIZE_OFLOW:
		this_cpu_inc(nic->drv_stats->tx_imm_size_oflow);
		break;
	case CQ_TX_ERROP_DATA_SEQUENCE_ERR:
		this_cpu_inc(nic->drv_stats->tx_data_seq_err);
		break;
	case CQ_TX_ERROP_MEM_SEQUENCE_ERR:
		this_cpu_inc(nic->drv_stats->tx_mem_seq_err);
		break;
	case CQ_TX_ERROP_LOCK_VIOL:
		this_cpu_inc(nic->drv_stats->tx_lock_viol);
		break;
	case CQ_TX_ERROP_DATA_FAULT:
		this_cpu_inc(nic->drv_stats->tx_data_fault);
		break;
	case CQ_TX_ERROP_TSTMP_CONFLICT:
		this_cpu_inc(nic->drv_stats->tx_tstmp_conflict);
		break;
	case CQ_TX_ERROP_TSTMP_TIMEOUT:
		this_cpu_inc(nic->drv_stats->tx_tstmp_timeout);
		break;
	case CQ_TX_ERROP_MEM_FAULT:
		this_cpu_inc(nic->drv_stats->tx_mem_fault);
		break;
	case CQ_TX_ERROP_CK_OVERLAP:
		this_cpu_inc(nic->drv_stats->tx_csum_overlap);
		break;
	case CQ_TX_ERROP_CK_OFLOW:
		this_cpu_inc(nic->drv_stats->tx_csum_overflow);
		break;
	}

	return 1;
}
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
typedef  int /*<<< orphan*/  u16 ;
struct creq_query_roce_stats_resp_sb {int /*<<< orphan*/  res_rx_pci_err; int /*<<< orphan*/  res_tx_pci_err; int /*<<< orphan*/  res_srq_load_err; int /*<<< orphan*/  res_cq_load_err; int /*<<< orphan*/  res_wqe_format_err; int /*<<< orphan*/  res_invalid_dup_rkey; int /*<<< orphan*/  res_cmp_err; int /*<<< orphan*/  res_srq_err; int /*<<< orphan*/  res_mem_error; int /*<<< orphan*/  res_rem_inv_err; int /*<<< orphan*/  res_unaligned_atomic; int /*<<< orphan*/  res_unsup_opcode; int /*<<< orphan*/  res_irrq_oflow; int /*<<< orphan*/  res_tx_range_err; int /*<<< orphan*/  res_tx_no_perm; int /*<<< orphan*/  res_tx_domain_err; int /*<<< orphan*/  res_tx_invalid_rkey; int /*<<< orphan*/  res_rx_range_err; int /*<<< orphan*/  res_rx_no_perm; int /*<<< orphan*/  res_rx_domain_err; int /*<<< orphan*/  res_rx_invalid_rkey; int /*<<< orphan*/  res_opcode_err; int /*<<< orphan*/  res_exceeds_wqe; int /*<<< orphan*/  res_length_mismatch; int /*<<< orphan*/  res_exceed_max; int /*<<< orphan*/  dup_req; int /*<<< orphan*/  remote_op_err; int /*<<< orphan*/  remote_access_err; int /*<<< orphan*/  remote_invalid_req_err; int /*<<< orphan*/  mem_mgmt_op_err; int /*<<< orphan*/  local_protection_err; int /*<<< orphan*/  local_qp_op_err; int /*<<< orphan*/  bad_resp_err; int /*<<< orphan*/  unrecoverable_err; int /*<<< orphan*/  missing_resp; int /*<<< orphan*/  rnr_naks_rcvd; int /*<<< orphan*/  max_retry_exceeded; int /*<<< orphan*/  seq_err_naks_rcvd; int /*<<< orphan*/  to_retransmits; } ;
struct creq_query_roce_stats_resp {int dummy; } ;
struct cmdq_query_roce_stats {int resp_size; } ;
struct bnxt_qplib_roce_stats {void* res_rx_pci_err; void* res_tx_pci_err; void* res_srq_load_err; void* res_cq_load_err; void* res_wqe_format_err; void* res_invalid_dup_rkey; void* res_cmp_err; void* res_srq_err; void* res_mem_error; void* res_rem_inv_err; void* res_unaligned_atomic; void* res_unsup_opcode; void* res_irrq_oflow; void* res_tx_range_err; void* res_tx_no_perm; void* res_tx_domain_err; void* res_tx_invalid_rkey; void* res_rx_range_err; void* res_rx_no_perm; void* res_rx_domain_err; void* res_rx_invalid_rkey; void* res_opcode_err; void* res_exceeds_wqe; void* res_length_mismatch; void* res_exceed_max; void* dup_req; void* remote_op_err; void* remote_access_err; void* remote_invalid_req_err; void* mem_mgmt_op_err; void* local_protection_err; void* local_qp_op_err; void* bad_resp_err; void* unrecoverable_err; void* missing_resp; void* rnr_naks_rcvd; void* max_retry_exceeded; void* seq_err_naks_rcvd; void* to_retransmits; } ;
struct bnxt_qplib_rcfw_sbuf {struct creq_query_roce_stats_resp_sb* sb; } ;
struct bnxt_qplib_rcfw {TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int BNXT_QPLIB_CMDQE_UNITS ; 
 int ENOMEM ; 
 int /*<<< orphan*/  QUERY_ROCE_STATS ; 
 int /*<<< orphan*/  RCFW_CMD_PREP (struct cmdq_query_roce_stats,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct bnxt_qplib_rcfw_sbuf* bnxt_qplib_rcfw_alloc_sbuf (struct bnxt_qplib_rcfw*,int) ; 
 int /*<<< orphan*/  bnxt_qplib_rcfw_free_sbuf (struct bnxt_qplib_rcfw*,struct bnxt_qplib_rcfw_sbuf*) ; 
 int bnxt_qplib_rcfw_send_message (struct bnxt_qplib_rcfw*,void*,void*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 void* le64_to_cpu (int /*<<< orphan*/ ) ; 

int bnxt_qplib_get_roce_stats(struct bnxt_qplib_rcfw *rcfw,
			      struct bnxt_qplib_roce_stats *stats)
{
	struct cmdq_query_roce_stats req;
	struct creq_query_roce_stats_resp resp;
	struct bnxt_qplib_rcfw_sbuf *sbuf;
	struct creq_query_roce_stats_resp_sb *sb;
	u16 cmd_flags = 0;
	int rc = 0;

	RCFW_CMD_PREP(req, QUERY_ROCE_STATS, cmd_flags);

	sbuf = bnxt_qplib_rcfw_alloc_sbuf(rcfw, sizeof(*sb));
	if (!sbuf) {
		dev_err(&rcfw->pdev->dev,
			"QPLIB: SP: QUERY_ROCE_STATS alloc side buffer failed");
		return -ENOMEM;
	}

	sb = sbuf->sb;
	req.resp_size = sizeof(*sb) / BNXT_QPLIB_CMDQE_UNITS;
	rc = bnxt_qplib_rcfw_send_message(rcfw, (void *)&req, (void *)&resp,
					  (void *)sbuf, 0);
	if (rc)
		goto bail;
	/* Extract the context from the side buffer */
	stats->to_retransmits = le64_to_cpu(sb->to_retransmits);
	stats->seq_err_naks_rcvd = le64_to_cpu(sb->seq_err_naks_rcvd);
	stats->max_retry_exceeded = le64_to_cpu(sb->max_retry_exceeded);
	stats->rnr_naks_rcvd = le64_to_cpu(sb->rnr_naks_rcvd);
	stats->missing_resp = le64_to_cpu(sb->missing_resp);
	stats->unrecoverable_err = le64_to_cpu(sb->unrecoverable_err);
	stats->bad_resp_err = le64_to_cpu(sb->bad_resp_err);
	stats->local_qp_op_err = le64_to_cpu(sb->local_qp_op_err);
	stats->local_protection_err = le64_to_cpu(sb->local_protection_err);
	stats->mem_mgmt_op_err = le64_to_cpu(sb->mem_mgmt_op_err);
	stats->remote_invalid_req_err = le64_to_cpu(sb->remote_invalid_req_err);
	stats->remote_access_err = le64_to_cpu(sb->remote_access_err);
	stats->remote_op_err = le64_to_cpu(sb->remote_op_err);
	stats->dup_req = le64_to_cpu(sb->dup_req);
	stats->res_exceed_max = le64_to_cpu(sb->res_exceed_max);
	stats->res_length_mismatch = le64_to_cpu(sb->res_length_mismatch);
	stats->res_exceeds_wqe = le64_to_cpu(sb->res_exceeds_wqe);
	stats->res_opcode_err = le64_to_cpu(sb->res_opcode_err);
	stats->res_rx_invalid_rkey = le64_to_cpu(sb->res_rx_invalid_rkey);
	stats->res_rx_domain_err = le64_to_cpu(sb->res_rx_domain_err);
	stats->res_rx_no_perm = le64_to_cpu(sb->res_rx_no_perm);
	stats->res_rx_range_err = le64_to_cpu(sb->res_rx_range_err);
	stats->res_tx_invalid_rkey = le64_to_cpu(sb->res_tx_invalid_rkey);
	stats->res_tx_domain_err = le64_to_cpu(sb->res_tx_domain_err);
	stats->res_tx_no_perm = le64_to_cpu(sb->res_tx_no_perm);
	stats->res_tx_range_err = le64_to_cpu(sb->res_tx_range_err);
	stats->res_irrq_oflow = le64_to_cpu(sb->res_irrq_oflow);
	stats->res_unsup_opcode = le64_to_cpu(sb->res_unsup_opcode);
	stats->res_unaligned_atomic = le64_to_cpu(sb->res_unaligned_atomic);
	stats->res_rem_inv_err = le64_to_cpu(sb->res_rem_inv_err);
	stats->res_mem_error = le64_to_cpu(sb->res_mem_error);
	stats->res_srq_err = le64_to_cpu(sb->res_srq_err);
	stats->res_cmp_err = le64_to_cpu(sb->res_cmp_err);
	stats->res_invalid_dup_rkey = le64_to_cpu(sb->res_invalid_dup_rkey);
	stats->res_wqe_format_err = le64_to_cpu(sb->res_wqe_format_err);
	stats->res_cq_load_err = le64_to_cpu(sb->res_cq_load_err);
	stats->res_srq_load_err = le64_to_cpu(sb->res_srq_load_err);
	stats->res_tx_pci_err = le64_to_cpu(sb->res_tx_pci_err);
	stats->res_rx_pci_err = le64_to_cpu(sb->res_rx_pci_err);
bail:
	bnxt_qplib_rcfw_free_sbuf(rcfw, sbuf);
	return rc;
}
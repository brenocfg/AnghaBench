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
struct hwrm_func_backing_store_qcaps_output {int tqm_entries_multiple; int /*<<< orphan*/  tim_max_entries; int /*<<< orphan*/  tim_entry_size; int /*<<< orphan*/  mrav_num_entries_units; int /*<<< orphan*/  mrav_entry_size; int /*<<< orphan*/  mrav_max_entries; int /*<<< orphan*/  tqm_max_entries_per_ring; int /*<<< orphan*/  tqm_min_entries_per_ring; int /*<<< orphan*/  tqm_entry_size; int /*<<< orphan*/  stat_entry_size; int /*<<< orphan*/  stat_max_entries; int /*<<< orphan*/  vnic_entry_size; int /*<<< orphan*/  vnic_max_ring_table_entries; int /*<<< orphan*/  vnic_max_vnic_entries; int /*<<< orphan*/  cq_entry_size; int /*<<< orphan*/  cq_max_entries; int /*<<< orphan*/  cq_max_l2_entries; int /*<<< orphan*/  srq_entry_size; int /*<<< orphan*/  srq_max_entries; int /*<<< orphan*/  srq_max_l2_entries; int /*<<< orphan*/  qp_entry_size; int /*<<< orphan*/  qp_max_l2_entries; int /*<<< orphan*/  qp_min_qp1_entries; int /*<<< orphan*/  qp_max_entries; } ;
struct hwrm_func_backing_store_qcaps_input {int /*<<< orphan*/  member_0; } ;
struct bnxt_ctx_pg_info {int dummy; } ;
struct bnxt_ctx_mem_info {int tqm_entries_multiple; void* tim_max_entries; void* tim_entry_size; void* mrav_num_entries_units; void* mrav_entry_size; void* mrav_max_entries; void* tqm_max_entries_per_ring; void* tqm_min_entries_per_ring; void* tqm_entry_size; void* stat_entry_size; void* stat_max_entries; void* vnic_entry_size; void* vnic_max_ring_table_entries; void* vnic_max_vnic_entries; void* cq_entry_size; void* cq_max_entries; void* cq_max_l2_entries; void* srq_entry_size; void* srq_max_entries; void* srq_max_l2_entries; void* qp_entry_size; void* qp_max_l2_entries; void* qp_min_qp1_entries; void* qp_max_entries; struct bnxt_ctx_pg_info** tqm_mem; } ;
struct bnxt {int hwrm_spec_code; int max_q; int /*<<< orphan*/  hwrm_cmd_lock; struct bnxt_ctx_mem_info* ctx; struct hwrm_func_backing_store_qcaps_output* hwrm_cmd_resp_addr; } ;
typedef  int /*<<< orphan*/  req ;

/* Variables and functions */
 scalar_t__ BNXT_VF (struct bnxt*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HWRM_CMD_TIMEOUT ; 
 int /*<<< orphan*/  HWRM_FUNC_BACKING_STORE_QCAPS ; 
 int _hwrm_send_message_silent (struct bnxt*,struct hwrm_func_backing_store_qcaps_input*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnxt_hwrm_cmd_hdr_init (struct bnxt*,struct hwrm_func_backing_store_qcaps_input*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  kfree (struct bnxt_ctx_mem_info*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 void* le16_to_cpu (int /*<<< orphan*/ ) ; 
 void* le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bnxt_hwrm_func_backing_store_qcaps(struct bnxt *bp)
{
	struct hwrm_func_backing_store_qcaps_input req = {0};
	struct hwrm_func_backing_store_qcaps_output *resp =
		bp->hwrm_cmd_resp_addr;
	int rc;

	if (bp->hwrm_spec_code < 0x10902 || BNXT_VF(bp) || bp->ctx)
		return 0;

	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_FUNC_BACKING_STORE_QCAPS, -1, -1);
	mutex_lock(&bp->hwrm_cmd_lock);
	rc = _hwrm_send_message_silent(bp, &req, sizeof(req), HWRM_CMD_TIMEOUT);
	if (!rc) {
		struct bnxt_ctx_pg_info *ctx_pg;
		struct bnxt_ctx_mem_info *ctx;
		int i;

		ctx = kzalloc(sizeof(*ctx), GFP_KERNEL);
		if (!ctx) {
			rc = -ENOMEM;
			goto ctx_err;
		}
		ctx_pg = kzalloc(sizeof(*ctx_pg) * (bp->max_q + 1), GFP_KERNEL);
		if (!ctx_pg) {
			kfree(ctx);
			rc = -ENOMEM;
			goto ctx_err;
		}
		for (i = 0; i < bp->max_q + 1; i++, ctx_pg++)
			ctx->tqm_mem[i] = ctx_pg;

		bp->ctx = ctx;
		ctx->qp_max_entries = le32_to_cpu(resp->qp_max_entries);
		ctx->qp_min_qp1_entries = le16_to_cpu(resp->qp_min_qp1_entries);
		ctx->qp_max_l2_entries = le16_to_cpu(resp->qp_max_l2_entries);
		ctx->qp_entry_size = le16_to_cpu(resp->qp_entry_size);
		ctx->srq_max_l2_entries = le16_to_cpu(resp->srq_max_l2_entries);
		ctx->srq_max_entries = le32_to_cpu(resp->srq_max_entries);
		ctx->srq_entry_size = le16_to_cpu(resp->srq_entry_size);
		ctx->cq_max_l2_entries = le16_to_cpu(resp->cq_max_l2_entries);
		ctx->cq_max_entries = le32_to_cpu(resp->cq_max_entries);
		ctx->cq_entry_size = le16_to_cpu(resp->cq_entry_size);
		ctx->vnic_max_vnic_entries =
			le16_to_cpu(resp->vnic_max_vnic_entries);
		ctx->vnic_max_ring_table_entries =
			le16_to_cpu(resp->vnic_max_ring_table_entries);
		ctx->vnic_entry_size = le16_to_cpu(resp->vnic_entry_size);
		ctx->stat_max_entries = le32_to_cpu(resp->stat_max_entries);
		ctx->stat_entry_size = le16_to_cpu(resp->stat_entry_size);
		ctx->tqm_entry_size = le16_to_cpu(resp->tqm_entry_size);
		ctx->tqm_min_entries_per_ring =
			le32_to_cpu(resp->tqm_min_entries_per_ring);
		ctx->tqm_max_entries_per_ring =
			le32_to_cpu(resp->tqm_max_entries_per_ring);
		ctx->tqm_entries_multiple = resp->tqm_entries_multiple;
		if (!ctx->tqm_entries_multiple)
			ctx->tqm_entries_multiple = 1;
		ctx->mrav_max_entries = le32_to_cpu(resp->mrav_max_entries);
		ctx->mrav_entry_size = le16_to_cpu(resp->mrav_entry_size);
		ctx->mrav_num_entries_units =
			le16_to_cpu(resp->mrav_num_entries_units);
		ctx->tim_entry_size = le16_to_cpu(resp->tim_entry_size);
		ctx->tim_max_entries = le32_to_cpu(resp->tim_max_entries);
	} else {
		rc = 0;
	}
ctx_err:
	mutex_unlock(&bp->hwrm_cmd_lock);
	return rc;
}
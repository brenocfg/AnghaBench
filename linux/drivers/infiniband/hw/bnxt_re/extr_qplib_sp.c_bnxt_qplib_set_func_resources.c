#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct creq_set_func_resources_resp {int dummy; } ;
struct cmdq_set_func_resources {void* max_gid_per_vf; void* max_cq_per_vf; void* max_srq_per_vf; void* max_mrw_per_vf; void* max_qp_per_vf; void* number_of_cq; void* number_of_srq; void* number_of_mrw; void* number_of_qp; } ;
struct bnxt_qplib_res {TYPE_2__* pdev; } ;
struct bnxt_qplib_rcfw {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  max_gid_per_vf; int /*<<< orphan*/  max_cq_per_vf; int /*<<< orphan*/  max_srq_per_vf; int /*<<< orphan*/  max_mrw_per_vf; int /*<<< orphan*/  max_qp_per_vf; } ;
struct bnxt_qplib_ctx {TYPE_1__ vf_res; int /*<<< orphan*/  cq_count; int /*<<< orphan*/  srqc_count; int /*<<< orphan*/  mrw_count; int /*<<< orphan*/  qpc_count; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  RCFW_CMD_PREP (struct cmdq_set_func_resources,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_FUNC_RESOURCES ; 
 int bnxt_qplib_rcfw_send_message (struct bnxt_qplib_rcfw*,void*,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 

int bnxt_qplib_set_func_resources(struct bnxt_qplib_res *res,
				  struct bnxt_qplib_rcfw *rcfw,
				  struct bnxt_qplib_ctx *ctx)
{
	struct cmdq_set_func_resources req;
	struct creq_set_func_resources_resp resp;
	u16 cmd_flags = 0;
	int rc = 0;

	RCFW_CMD_PREP(req, SET_FUNC_RESOURCES, cmd_flags);

	req.number_of_qp = cpu_to_le32(ctx->qpc_count);
	req.number_of_mrw = cpu_to_le32(ctx->mrw_count);
	req.number_of_srq =  cpu_to_le32(ctx->srqc_count);
	req.number_of_cq = cpu_to_le32(ctx->cq_count);

	req.max_qp_per_vf = cpu_to_le32(ctx->vf_res.max_qp_per_vf);
	req.max_mrw_per_vf = cpu_to_le32(ctx->vf_res.max_mrw_per_vf);
	req.max_srq_per_vf = cpu_to_le32(ctx->vf_res.max_srq_per_vf);
	req.max_cq_per_vf = cpu_to_le32(ctx->vf_res.max_cq_per_vf);
	req.max_gid_per_vf = cpu_to_le32(ctx->vf_res.max_gid_per_vf);

	rc = bnxt_qplib_rcfw_send_message(rcfw, (void *)&req,
					  (void *)&resp,
					  NULL, 0);
	if (rc) {
		dev_err(&res->pdev->dev, "Failed to set function resources\n");
	}
	return rc;
}
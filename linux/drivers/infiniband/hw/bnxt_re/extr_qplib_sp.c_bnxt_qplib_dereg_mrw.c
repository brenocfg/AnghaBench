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
struct creq_deregister_mr_resp {int dummy; } ;
struct cmdq_deregister_mr {int /*<<< orphan*/  lkey; } ;
struct bnxt_qplib_res {int /*<<< orphan*/  pdev; struct bnxt_qplib_rcfw* rcfw; } ;
struct bnxt_qplib_rcfw {int dummy; } ;
struct TYPE_2__ {scalar_t__ max_elements; } ;
struct bnxt_qplib_mrw {TYPE_1__ hwq; scalar_t__ total_size; scalar_t__ va; int /*<<< orphan*/  lkey; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEREGISTER_MR ; 
 int /*<<< orphan*/  RCFW_CMD_PREP (struct cmdq_deregister_mr,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnxt_qplib_free_hwq (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int bnxt_qplib_rcfw_send_message (struct bnxt_qplib_rcfw*,void*,void*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 

int bnxt_qplib_dereg_mrw(struct bnxt_qplib_res *res, struct bnxt_qplib_mrw *mrw,
			 bool block)
{
	struct bnxt_qplib_rcfw *rcfw = res->rcfw;
	struct cmdq_deregister_mr req;
	struct creq_deregister_mr_resp resp;
	u16 cmd_flags = 0;
	int rc;

	RCFW_CMD_PREP(req, DEREGISTER_MR, cmd_flags);

	req.lkey = cpu_to_le32(mrw->lkey);
	rc = bnxt_qplib_rcfw_send_message(rcfw, (void *)&req,
					  (void *)&resp, NULL, block);
	if (rc)
		return rc;

	/* Free the qplib's MR memory */
	if (mrw->hwq.max_elements) {
		mrw->va = 0;
		mrw->total_size = 0;
		bnxt_qplib_free_hwq(res->pdev, &mrw->hwq);
	}

	return 0;
}
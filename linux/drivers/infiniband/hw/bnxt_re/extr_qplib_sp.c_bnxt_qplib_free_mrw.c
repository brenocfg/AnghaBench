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
struct creq_deallocate_key_resp {int dummy; } ;
struct cmdq_deallocate_key {scalar_t__ mrw_flags; void* key; } ;
struct bnxt_qplib_res {TYPE_1__* pdev; struct bnxt_qplib_rcfw* rcfw; } ;
struct bnxt_qplib_rcfw {int dummy; } ;
struct TYPE_4__ {scalar_t__ max_elements; } ;
struct bnxt_qplib_mrw {int lkey; scalar_t__ type; int rkey; TYPE_2__ hwq; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ CMDQ_ALLOCATE_MRW_MRW_FLAGS_MW_TYPE1 ; 
 scalar_t__ CMDQ_ALLOCATE_MRW_MRW_FLAGS_MW_TYPE2A ; 
 scalar_t__ CMDQ_ALLOCATE_MRW_MRW_FLAGS_MW_TYPE2B ; 
 int /*<<< orphan*/  DEALLOCATE_KEY ; 
 int /*<<< orphan*/  RCFW_CMD_PREP (struct cmdq_deallocate_key,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnxt_qplib_free_hwq (TYPE_1__*,TYPE_2__*) ; 
 int bnxt_qplib_rcfw_send_message (struct bnxt_qplib_rcfw*,void*,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* cpu_to_le32 (int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 

int bnxt_qplib_free_mrw(struct bnxt_qplib_res *res, struct bnxt_qplib_mrw *mrw)
{
	struct bnxt_qplib_rcfw *rcfw = res->rcfw;
	struct cmdq_deallocate_key req;
	struct creq_deallocate_key_resp resp;
	u16 cmd_flags = 0;
	int rc;

	if (mrw->lkey == 0xFFFFFFFF) {
		dev_info(&res->pdev->dev, "SP: Free a reserved lkey MRW\n");
		return 0;
	}

	RCFW_CMD_PREP(req, DEALLOCATE_KEY, cmd_flags);

	req.mrw_flags = mrw->type;

	if ((mrw->type == CMDQ_ALLOCATE_MRW_MRW_FLAGS_MW_TYPE1)  ||
	    (mrw->type == CMDQ_ALLOCATE_MRW_MRW_FLAGS_MW_TYPE2A) ||
	    (mrw->type == CMDQ_ALLOCATE_MRW_MRW_FLAGS_MW_TYPE2B))
		req.key = cpu_to_le32(mrw->rkey);
	else
		req.key = cpu_to_le32(mrw->lkey);

	rc = bnxt_qplib_rcfw_send_message(rcfw, (void *)&req, (void *)&resp,
					  NULL, 0);
	if (rc)
		return rc;

	/* Free the qplib's MRW memory */
	if (mrw->hwq.max_elements)
		bnxt_qplib_free_hwq(res->pdev, &mrw->hwq);

	return 0;
}
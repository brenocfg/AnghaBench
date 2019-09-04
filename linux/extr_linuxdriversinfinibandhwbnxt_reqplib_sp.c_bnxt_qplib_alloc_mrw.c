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
struct creq_allocate_mrw_resp {int /*<<< orphan*/  xid; } ;
struct cmdq_allocate_mrw {scalar_t__ mrw_flags; int /*<<< orphan*/  mrw_handle; int /*<<< orphan*/  access; int /*<<< orphan*/  pd_id; } ;
struct bnxt_qplib_res {struct bnxt_qplib_rcfw* rcfw; } ;
struct bnxt_qplib_rcfw {int dummy; } ;
struct bnxt_qplib_mrw {scalar_t__ type; int flags; void* lkey; void* rkey; TYPE_1__* pd; } ;
struct TYPE_2__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOCATE_MRW ; 
 int BNXT_QPLIB_FR_PMR ; 
 int /*<<< orphan*/  CMDQ_ALLOCATE_MRW_ACCESS_CONSUMER_OWNED_KEY ; 
 scalar_t__ CMDQ_ALLOCATE_MRW_MRW_FLAGS_MW_TYPE1 ; 
 scalar_t__ CMDQ_ALLOCATE_MRW_MRW_FLAGS_MW_TYPE2A ; 
 scalar_t__ CMDQ_ALLOCATE_MRW_MRW_FLAGS_MW_TYPE2B ; 
 scalar_t__ CMDQ_ALLOCATE_MRW_MRW_FLAGS_PMR ; 
 int /*<<< orphan*/  RCFW_CMD_PREP (struct cmdq_allocate_mrw,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int bnxt_qplib_rcfw_send_message (struct bnxt_qplib_rcfw*,void*,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le64 (unsigned long) ; 
 void* le32_to_cpu (int /*<<< orphan*/ ) ; 

int bnxt_qplib_alloc_mrw(struct bnxt_qplib_res *res, struct bnxt_qplib_mrw *mrw)
{
	struct bnxt_qplib_rcfw *rcfw = res->rcfw;
	struct cmdq_allocate_mrw req;
	struct creq_allocate_mrw_resp resp;
	u16 cmd_flags = 0;
	unsigned long tmp;
	int rc;

	RCFW_CMD_PREP(req, ALLOCATE_MRW, cmd_flags);

	req.pd_id = cpu_to_le32(mrw->pd->id);
	req.mrw_flags = mrw->type;
	if ((mrw->type == CMDQ_ALLOCATE_MRW_MRW_FLAGS_PMR &&
	     mrw->flags & BNXT_QPLIB_FR_PMR) ||
	    mrw->type == CMDQ_ALLOCATE_MRW_MRW_FLAGS_MW_TYPE2A ||
	    mrw->type == CMDQ_ALLOCATE_MRW_MRW_FLAGS_MW_TYPE2B)
		req.access = CMDQ_ALLOCATE_MRW_ACCESS_CONSUMER_OWNED_KEY;
	tmp = (unsigned long)mrw;
	req.mrw_handle = cpu_to_le64(tmp);

	rc = bnxt_qplib_rcfw_send_message(rcfw, (void *)&req,
					  (void *)&resp, NULL, 0);
	if (rc)
		return rc;

	if ((mrw->type == CMDQ_ALLOCATE_MRW_MRW_FLAGS_MW_TYPE1)  ||
	    (mrw->type == CMDQ_ALLOCATE_MRW_MRW_FLAGS_MW_TYPE2A) ||
	    (mrw->type == CMDQ_ALLOCATE_MRW_MRW_FLAGS_MW_TYPE2B))
		mrw->rkey = le32_to_cpu(resp.xid);
	else
		mrw->lkey = le32_to_cpu(resp.xid);
	return 0;
}
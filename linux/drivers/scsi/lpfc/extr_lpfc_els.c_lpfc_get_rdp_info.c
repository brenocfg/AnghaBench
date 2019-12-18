#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct lpfc_rdp_context {TYPE_1__* ndlp; } ;
struct lpfc_hba {int /*<<< orphan*/  mbox_mem_pool; } ;
struct TYPE_8__ {struct lpfc_rdp_context* ctx_ndlp; int /*<<< orphan*/  mbox_cmpl; int /*<<< orphan*/  vport; } ;
struct TYPE_7__ {int /*<<< orphan*/  vport; } ;
typedef  TYPE_2__ LPFC_MBOXQ_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  KERN_WARNING ; 
 int LOG_ELS ; 
 int LOG_MBOX ; 
 int MBX_NOT_FINISHED ; 
 int /*<<< orphan*/  MBX_NOWAIT ; 
 int /*<<< orphan*/  lpfc_mbx_cmpl_rdp_page_a0 ; 
 int /*<<< orphan*/  lpfc_printf_log (struct lpfc_hba*,int /*<<< orphan*/ ,int,char*) ; 
 scalar_t__ lpfc_sli4_dump_page_a0 (struct lpfc_hba*,TYPE_2__*) ; 
 int lpfc_sli_issue_mbox (struct lpfc_hba*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* mempool_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mempool_free (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
lpfc_get_rdp_info(struct lpfc_hba *phba, struct lpfc_rdp_context *rdp_context)
{
	LPFC_MBOXQ_t *mbox = NULL;
	int rc;

	mbox = mempool_alloc(phba->mbox_mem_pool, GFP_KERNEL);
	if (!mbox) {
		lpfc_printf_log(phba, KERN_WARNING, LOG_MBOX | LOG_ELS,
				"7105 failed to allocate mailbox memory");
		return 1;
	}

	if (lpfc_sli4_dump_page_a0(phba, mbox))
		goto prep_mbox_fail;
	mbox->vport = rdp_context->ndlp->vport;
	mbox->mbox_cmpl = lpfc_mbx_cmpl_rdp_page_a0;
	mbox->ctx_ndlp = (struct lpfc_rdp_context *)rdp_context;
	rc = lpfc_sli_issue_mbox(phba, mbox, MBX_NOWAIT);
	if (rc == MBX_NOT_FINISHED)
		goto issue_mbox_fail;

	return 0;

prep_mbox_fail:
issue_mbox_fail:
	mempool_free(mbox, phba->mbox_mem_pool);
	return 1;
}
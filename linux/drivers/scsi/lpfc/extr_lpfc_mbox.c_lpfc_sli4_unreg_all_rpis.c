#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct lpfc_vport {size_t vpi; struct lpfc_hba* phba; } ;
struct lpfc_hba {int /*<<< orphan*/  mbox_mem_pool; int /*<<< orphan*/ * vpi_ids; } ;
struct TYPE_10__ {int rsvd1; } ;
struct TYPE_11__ {TYPE_1__ varUnregLogin; } ;
struct TYPE_12__ {TYPE_2__ un; } ;
struct TYPE_13__ {TYPE_3__ mb; } ;
struct TYPE_14__ {int /*<<< orphan*/ * ctx_ndlp; int /*<<< orphan*/  mbox_cmpl; struct lpfc_vport* vport; TYPE_4__ u; } ;
typedef  TYPE_5__ LPFC_MBOXQ_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MBX_NOT_FINISHED ; 
 int /*<<< orphan*/  MBX_NOWAIT ; 
 int /*<<< orphan*/  lpfc_sli_def_mbox_cmpl ; 
 int lpfc_sli_issue_mbox (struct lpfc_hba*,TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_unreg_login (struct lpfc_hba*,size_t,int /*<<< orphan*/ ,TYPE_5__*) ; 
 TYPE_5__* mempool_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mempool_free (TYPE_5__*,int /*<<< orphan*/ ) ; 

void
lpfc_sli4_unreg_all_rpis(struct lpfc_vport *vport)
{
	struct lpfc_hba  *phba  = vport->phba;
	LPFC_MBOXQ_t     *mbox;
	int rc;

	mbox = mempool_alloc(phba->mbox_mem_pool, GFP_KERNEL);
	if (mbox) {
		/*
		 * For SLI4 functions, the rpi field is overloaded for
		 * the vport context unreg all.  This routine passes
		 * 0 for the rpi field in lpfc_unreg_login for compatibility
		 * with SLI3 and then overrides the rpi field with the
		 * expected value for SLI4.
		 */
		lpfc_unreg_login(phba, vport->vpi, phba->vpi_ids[vport->vpi],
				 mbox);
		mbox->u.mb.un.varUnregLogin.rsvd1 = 0x4000;
		mbox->vport = vport;
		mbox->mbox_cmpl = lpfc_sli_def_mbox_cmpl;
		mbox->ctx_ndlp = NULL;
		rc = lpfc_sli_issue_mbox(phba, mbox, MBX_NOWAIT);
		if (rc == MBX_NOT_FINISHED)
			mempool_free(mbox, phba->mbox_mem_pool);
	}
}
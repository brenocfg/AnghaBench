#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct lpfc_rdp_context {int /*<<< orphan*/  (* cmpl ) (struct lpfc_hba*,struct lpfc_rdp_context*,int) ;int /*<<< orphan*/  link_stat; } ;
struct lpfc_hba {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  varRdLnk; } ;
struct TYPE_9__ {TYPE_1__ un; scalar_t__ mbxStatus; } ;
struct TYPE_8__ {TYPE_3__ mb; } ;
struct TYPE_10__ {TYPE_2__ u; scalar_t__ ctx_ndlp; } ;
typedef  int /*<<< orphan*/  READ_LNK_VAR ;
typedef  TYPE_3__ MAILBOX_t ;
typedef  TYPE_4__ LPFC_MBOXQ_t ;

/* Variables and functions */
 int FAILURE ; 
 int SUCCESS ; 
 int /*<<< orphan*/  lpfc_sli4_mbox_cmd_free (struct lpfc_hba*,TYPE_4__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub1 (struct lpfc_hba*,struct lpfc_rdp_context*,int) ; 

__attribute__((used)) static void
lpfc_mbx_cmpl_rdp_link_stat(struct lpfc_hba *phba, LPFC_MBOXQ_t *mboxq)
{
	MAILBOX_t *mb;
	int rc = FAILURE;
	struct lpfc_rdp_context *rdp_context =
			(struct lpfc_rdp_context *)(mboxq->ctx_ndlp);

	mb = &mboxq->u.mb;
	if (mb->mbxStatus)
		goto mbx_failed;

	memcpy(&rdp_context->link_stat, &mb->un.varRdLnk, sizeof(READ_LNK_VAR));

	rc = SUCCESS;

mbx_failed:
	lpfc_sli4_mbox_cmd_free(phba, mboxq);
	rdp_context->cmpl(phba, rdp_context, rc);
}
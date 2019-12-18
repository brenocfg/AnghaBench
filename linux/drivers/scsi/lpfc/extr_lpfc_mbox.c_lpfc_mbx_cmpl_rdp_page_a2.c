#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct lpfc_rdp_context {int /*<<< orphan*/  (* cmpl ) (struct lpfc_hba*,struct lpfc_rdp_context*,int /*<<< orphan*/ ) ;TYPE_2__* ndlp; int /*<<< orphan*/  page_a2; } ;
struct lpfc_hba {int dummy; } ;
struct lpfc_dmabuf {int /*<<< orphan*/  phys; int /*<<< orphan*/  virt; } ;
struct TYPE_9__ {int /*<<< orphan*/  mqe; } ;
struct TYPE_11__ {struct lpfc_rdp_context* ctx_ndlp; int /*<<< orphan*/  mbox_cmpl; int /*<<< orphan*/  vport; TYPE_1__ u; scalar_t__ ctx_buf; } ;
struct TYPE_10__ {int /*<<< orphan*/  vport; } ;
typedef  TYPE_3__ LPFC_MBOXQ_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMP_SFF_PAGE_A2_SIZE ; 
 int /*<<< orphan*/  FAILURE ; 
 scalar_t__ MBX_NOT_FINISHED ; 
 int /*<<< orphan*/  MBX_NOWAIT ; 
 scalar_t__ bf_get (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct lpfc_dmabuf*) ; 
 int /*<<< orphan*/  lpfc_mbuf_free (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_mbx_cmpl_rdp_link_stat ; 
 int /*<<< orphan*/  lpfc_mqe_status ; 
 int /*<<< orphan*/  lpfc_read_lnk_stat (struct lpfc_hba*,TYPE_3__*) ; 
 int /*<<< orphan*/  lpfc_sli4_mbox_cmd_free (struct lpfc_hba*,TYPE_3__*) ; 
 int /*<<< orphan*/  lpfc_sli_bemem_bcopy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ lpfc_sli_issue_mbox (struct lpfc_hba*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct lpfc_hba*,struct lpfc_rdp_context*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
lpfc_mbx_cmpl_rdp_page_a2(struct lpfc_hba *phba, LPFC_MBOXQ_t *mbox)
{
	struct lpfc_dmabuf *mp = (struct lpfc_dmabuf *)mbox->ctx_buf;
	struct lpfc_rdp_context *rdp_context =
			(struct lpfc_rdp_context *)(mbox->ctx_ndlp);

	if (bf_get(lpfc_mqe_status, &mbox->u.mqe))
		goto error_mbuf_free;

	lpfc_sli_bemem_bcopy(mp->virt, &rdp_context->page_a2,
				DMP_SFF_PAGE_A2_SIZE);

	/* We don't need dma buffer for link stat. */
	lpfc_mbuf_free(phba, mp->virt, mp->phys);
	kfree(mp);

	memset(mbox, 0, sizeof(*mbox));
	lpfc_read_lnk_stat(phba, mbox);
	mbox->vport = rdp_context->ndlp->vport;
	mbox->mbox_cmpl = lpfc_mbx_cmpl_rdp_link_stat;
	mbox->ctx_ndlp = (struct lpfc_rdp_context *)rdp_context;
	if (lpfc_sli_issue_mbox(phba, mbox, MBX_NOWAIT) == MBX_NOT_FINISHED)
		goto error_cmd_free;

	return;

error_mbuf_free:
	lpfc_mbuf_free(phba, mp->virt, mp->phys);
	kfree(mp);
error_cmd_free:
	lpfc_sli4_mbox_cmd_free(phba, mbox);
	rdp_context->cmpl(phba, rdp_context, FAILURE);
}
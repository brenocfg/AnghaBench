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
struct TYPE_2__ {int /*<<< orphan*/ * ndlp; } ;
struct lpfc_iocbq {int /*<<< orphan*/ * context3; int /*<<< orphan*/ * context2; int /*<<< orphan*/ * context1; TYPE_1__ context_un; } ;
struct lpfc_hba {int dummy; } ;
struct lpfc_dmabuf {int /*<<< orphan*/  phys; int /*<<< orphan*/  virt; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct lpfc_dmabuf*) ; 
 int /*<<< orphan*/  lpfc_free_ct_rsp (struct lpfc_hba*,struct lpfc_dmabuf*) ; 
 int /*<<< orphan*/  lpfc_mbuf_free (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_nlp_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lpfc_sli_release_iocbq (struct lpfc_hba*,struct lpfc_iocbq*) ; 

int
lpfc_ct_free_iocb(struct lpfc_hba *phba, struct lpfc_iocbq *ctiocb)
{
	struct lpfc_dmabuf *buf_ptr;

	if (ctiocb->context_un.ndlp) {
		lpfc_nlp_put(ctiocb->context_un.ndlp);
		ctiocb->context_un.ndlp = NULL;
	}
	if (ctiocb->context1) {
		buf_ptr = (struct lpfc_dmabuf *) ctiocb->context1;
		lpfc_mbuf_free(phba, buf_ptr->virt, buf_ptr->phys);
		kfree(buf_ptr);
		ctiocb->context1 = NULL;
	}
	if (ctiocb->context2) {
		lpfc_free_ct_rsp(phba, (struct lpfc_dmabuf *) ctiocb->context2);
		ctiocb->context2 = NULL;
	}

	if (ctiocb->context3) {
		buf_ptr = (struct lpfc_dmabuf *) ctiocb->context3;
		lpfc_mbuf_free(phba, buf_ptr->virt, buf_ptr->phys);
		kfree(buf_ptr);
		ctiocb->context3 = NULL;
	}
	lpfc_sli_release_iocbq(phba, ctiocb);
	return 0;
}
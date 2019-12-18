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
typedef  int uint32_t ;
struct nvmefc_ls_req {int /*<<< orphan*/  (* done ) (struct nvmefc_ls_req*,int) ;} ;
struct lpfc_wcqe_complete {int parameter; } ;
struct lpfc_vport {TYPE_1__* localport; } ;
struct lpfc_nvme_lport {int /*<<< orphan*/  cmpl_ls_err; int /*<<< orphan*/  cmpl_ls_xb; int /*<<< orphan*/  fc4NvmeLsCmpls; } ;
struct lpfc_nodelist {int /*<<< orphan*/  nlp_DID; } ;
struct lpfc_iocbq {int /*<<< orphan*/ * context1; int /*<<< orphan*/  sli4_xritag; int /*<<< orphan*/ * context3; scalar_t__ context2; struct lpfc_vport* vport; } ;
struct lpfc_hba {int dummy; } ;
struct lpfc_dmabuf {int /*<<< orphan*/  phys; int /*<<< orphan*/  virt; } ;
struct TYPE_2__ {scalar_t__ private; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  LOG_NVME_DISC ; 
 int LPFC_IOCB_STATUS_MASK ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int bf_get (int /*<<< orphan*/ ,struct lpfc_wcqe_complete*) ; 
 int /*<<< orphan*/  kfree (struct lpfc_dmabuf*) ; 
 int /*<<< orphan*/  lpfc_mbuf_free (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_nlp_put (struct lpfc_nodelist*) ; 
 int /*<<< orphan*/  lpfc_nvmeio_data (struct lpfc_hba*,char*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  lpfc_printf_vlog (struct lpfc_vport*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct nvmefc_ls_req*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,...) ; 
 int /*<<< orphan*/  lpfc_sli_release_iocbq (struct lpfc_hba*,struct lpfc_iocbq*) ; 
 int /*<<< orphan*/  lpfc_wcqe_c_status ; 
 int /*<<< orphan*/  lpfc_wcqe_c_xb ; 
 int /*<<< orphan*/  stub1 (struct nvmefc_ls_req*,int) ; 

__attribute__((used)) static void
lpfc_nvme_cmpl_gen_req(struct lpfc_hba *phba, struct lpfc_iocbq *cmdwqe,
		       struct lpfc_wcqe_complete *wcqe)
{
	struct lpfc_vport *vport = cmdwqe->vport;
	struct lpfc_nvme_lport *lport;
	uint32_t status;
	struct nvmefc_ls_req *pnvme_lsreq;
	struct lpfc_dmabuf *buf_ptr;
	struct lpfc_nodelist *ndlp;

	pnvme_lsreq = (struct nvmefc_ls_req *)cmdwqe->context2;
	status = bf_get(lpfc_wcqe_c_status, wcqe) & LPFC_IOCB_STATUS_MASK;

	if (vport->localport) {
		lport = (struct lpfc_nvme_lport *)vport->localport->private;
		if (lport) {
			atomic_inc(&lport->fc4NvmeLsCmpls);
			if (status) {
				if (bf_get(lpfc_wcqe_c_xb, wcqe))
					atomic_inc(&lport->cmpl_ls_xb);
				atomic_inc(&lport->cmpl_ls_err);
			}
		}
	}

	ndlp = (struct lpfc_nodelist *)cmdwqe->context1;
	lpfc_printf_vlog(vport, KERN_INFO, LOG_NVME_DISC,
			 "6047 nvme cmpl Enter "
			 "Data %px DID %x Xri: %x status %x reason x%x "
			 "cmd:x%px lsreg:x%px bmp:x%px ndlp:x%px\n",
			 pnvme_lsreq, ndlp ? ndlp->nlp_DID : 0,
			 cmdwqe->sli4_xritag, status,
			 (wcqe->parameter & 0xffff),
			 cmdwqe, pnvme_lsreq, cmdwqe->context3, ndlp);

	lpfc_nvmeio_data(phba, "NVME LS  CMPL: xri x%x stat x%x parm x%x\n",
			 cmdwqe->sli4_xritag, status, wcqe->parameter);

	if (cmdwqe->context3) {
		buf_ptr = (struct lpfc_dmabuf *)cmdwqe->context3;
		lpfc_mbuf_free(phba, buf_ptr->virt, buf_ptr->phys);
		kfree(buf_ptr);
		cmdwqe->context3 = NULL;
	}
	if (pnvme_lsreq->done)
		pnvme_lsreq->done(pnvme_lsreq, status);
	else
		lpfc_printf_vlog(vport, KERN_ERR, LOG_NVME_DISC,
				 "6046 nvme cmpl without done call back? "
				 "Data %px DID %x Xri: %x status %x\n",
				pnvme_lsreq, ndlp ? ndlp->nlp_DID : 0,
				cmdwqe->sli4_xritag, status);
	if (ndlp) {
		lpfc_nlp_put(ndlp);
		cmdwqe->context1 = NULL;
	}
	lpfc_sli_release_iocbq(phba, cmdwqe);
}
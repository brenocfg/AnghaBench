#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {int abort_tag; } ;
struct TYPE_17__ {int request_payload_len; TYPE_9__ wqe_com; TYPE_9__ wge_ctl; } ;
struct TYPE_12__ {int bdeSize; scalar_t__ bdeFlags; } ;
struct TYPE_13__ {TYPE_3__ f; } ;
struct TYPE_14__ {int /*<<< orphan*/  addrHigh; int /*<<< orphan*/  addrLow; TYPE_4__ tus; } ;
struct TYPE_15__ {TYPE_5__ bde; } ;
union lpfc_wqe128 {TYPE_8__ gen_req; TYPE_6__ generic; } ;
typedef  union lpfc_wqe {int dummy; } lpfc_wqe ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct TYPE_10__ {scalar_t__ bdeFlags; scalar_t__ bdeSize; } ;
struct TYPE_11__ {TYPE_1__ f; int /*<<< orphan*/  w; } ;
struct ulp_bde64 {int /*<<< orphan*/  addrHigh; int /*<<< orphan*/  addrLow; TYPE_2__ tus; } ;
struct nvmefc_ls_req {int dummy; } ;
struct lpfc_vport {int /*<<< orphan*/  port_state; struct lpfc_hba* phba; } ;
struct lpfc_nodelist {size_t nlp_rpi; int /*<<< orphan*/  nlp_DID; } ;
struct lpfc_iocbq {int rsvd2; int sli4_xritag; int iotag; void (* wqe_cmpl ) (struct lpfc_hba*,struct lpfc_iocbq*,struct lpfc_wcqe_complete*) ;int /*<<< orphan*/  retry; struct lpfc_vport* vport; scalar_t__ drvrTimeout; int /*<<< orphan*/ * iocb_cmpl; scalar_t__ hba_wqidx; int /*<<< orphan*/ * context2; int /*<<< orphan*/  context1; int /*<<< orphan*/  iocb_flag; int /*<<< orphan*/ * context3; union lpfc_wqe128 wqe; } ;
struct TYPE_16__ {int* rpi_ids; int /*<<< orphan*/ * hdwq; } ;
struct lpfc_hba {int fc_ratov; TYPE_7__ sli4_hba; } ;
struct lpfc_dmabuf {scalar_t__ virt; } ;

/* Variables and functions */
 scalar_t__ BUFF_TYPE_BDE_64 ; 
 int CLASS3 ; 
 int CMD_GEN_REQUEST64_WQE ; 
 int FC_RCTL_ELS4_REQ ; 
 int FC_TYPE_NVME ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  LOG_ELS ; 
 scalar_t__ LPFC_DRVR_TIMEOUT ; 
 int /*<<< orphan*/  LPFC_IO_NVME_LS ; 
 int LPFC_WQE_CQ_ID_DEFAULT ; 
 int LPFC_WQE_IOD_READ ; 
 int LPFC_WQE_LENLOC_NONE ; 
 int OTHER_COMMAND ; 
 int SLI4_CT_RPI ; 
 int /*<<< orphan*/  bf_set (int /*<<< orphan*/ ,TYPE_9__*,int) ; 
 int /*<<< orphan*/  lpfc_nlp_get (struct lpfc_nodelist*) ; 
 int /*<<< orphan*/  lpfc_nvmeio_data (struct lpfc_hba*,char*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_printf_vlog (struct lpfc_vport*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,...) ; 
 int lpfc_sli4_issue_wqe (struct lpfc_hba*,int /*<<< orphan*/ *,struct lpfc_iocbq*) ; 
 struct lpfc_iocbq* lpfc_sli_get_iocbq (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_sli_release_iocbq (struct lpfc_hba*,struct lpfc_iocbq*) ; 
 int /*<<< orphan*/  memset (union lpfc_wqe128*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wqe_class ; 
 int /*<<< orphan*/  wqe_cmd_type ; 
 int /*<<< orphan*/  wqe_cmnd ; 
 int /*<<< orphan*/  wqe_cqid ; 
 int /*<<< orphan*/  wqe_ct ; 
 int /*<<< orphan*/  wqe_ctxt_tag ; 
 int /*<<< orphan*/  wqe_dbde ; 
 int /*<<< orphan*/  wqe_dfctl ; 
 int /*<<< orphan*/  wqe_ebde_cnt ; 
 int /*<<< orphan*/  wqe_iod ; 
 int /*<<< orphan*/  wqe_la ; 
 int /*<<< orphan*/  wqe_lenloc ; 
 int /*<<< orphan*/  wqe_qosd ; 
 int /*<<< orphan*/  wqe_rctl ; 
 int /*<<< orphan*/  wqe_reqtag ; 
 int /*<<< orphan*/  wqe_si ; 
 int /*<<< orphan*/  wqe_tmo ; 
 int /*<<< orphan*/  wqe_type ; 
 int /*<<< orphan*/  wqe_xri_tag ; 

__attribute__((used)) static int
lpfc_nvme_gen_req(struct lpfc_vport *vport, struct lpfc_dmabuf *bmp,
		  struct lpfc_dmabuf *inp,
		  struct nvmefc_ls_req *pnvme_lsreq,
		  void (*cmpl)(struct lpfc_hba *, struct lpfc_iocbq *,
			       struct lpfc_wcqe_complete *),
		  struct lpfc_nodelist *ndlp, uint32_t num_entry,
		  uint32_t tmo, uint8_t retry)
{
	struct lpfc_hba *phba = vport->phba;
	union lpfc_wqe128 *wqe;
	struct lpfc_iocbq *genwqe;
	struct ulp_bde64 *bpl;
	struct ulp_bde64 bde;
	int i, rc, xmit_len, first_len;

	/* Allocate buffer for  command WQE */
	genwqe = lpfc_sli_get_iocbq(phba);
	if (genwqe == NULL)
		return 1;

	wqe = &genwqe->wqe;
	/* Initialize only 64 bytes */
	memset(wqe, 0, sizeof(union lpfc_wqe));

	genwqe->context3 = (uint8_t *)bmp;
	genwqe->iocb_flag |= LPFC_IO_NVME_LS;

	/* Save for completion so we can release these resources */
	genwqe->context1 = lpfc_nlp_get(ndlp);
	genwqe->context2 = (uint8_t *)pnvme_lsreq;
	/* Fill in payload, bp points to frame payload */

	if (!tmo)
		/* FC spec states we need 3 * ratov for CT requests */
		tmo = (3 * phba->fc_ratov);

	/* For this command calculate the xmit length of the request bde. */
	xmit_len = 0;
	first_len = 0;
	bpl = (struct ulp_bde64 *)bmp->virt;
	for (i = 0; i < num_entry; i++) {
		bde.tus.w = bpl[i].tus.w;
		if (bde.tus.f.bdeFlags != BUFF_TYPE_BDE_64)
			break;
		xmit_len += bde.tus.f.bdeSize;
		if (i == 0)
			first_len = xmit_len;
	}

	genwqe->rsvd2 = num_entry;
	genwqe->hba_wqidx = 0;

	/* Words 0 - 2 */
	wqe->generic.bde.tus.f.bdeFlags = BUFF_TYPE_BDE_64;
	wqe->generic.bde.tus.f.bdeSize = first_len;
	wqe->generic.bde.addrLow = bpl[0].addrLow;
	wqe->generic.bde.addrHigh = bpl[0].addrHigh;

	/* Word 3 */
	wqe->gen_req.request_payload_len = first_len;

	/* Word 4 */

	/* Word 5 */
	bf_set(wqe_dfctl, &wqe->gen_req.wge_ctl, 0);
	bf_set(wqe_si, &wqe->gen_req.wge_ctl, 1);
	bf_set(wqe_la, &wqe->gen_req.wge_ctl, 1);
	bf_set(wqe_rctl, &wqe->gen_req.wge_ctl, FC_RCTL_ELS4_REQ);
	bf_set(wqe_type, &wqe->gen_req.wge_ctl, FC_TYPE_NVME);

	/* Word 6 */
	bf_set(wqe_ctxt_tag, &wqe->gen_req.wqe_com,
	       phba->sli4_hba.rpi_ids[ndlp->nlp_rpi]);
	bf_set(wqe_xri_tag, &wqe->gen_req.wqe_com, genwqe->sli4_xritag);

	/* Word 7 */
	bf_set(wqe_tmo, &wqe->gen_req.wqe_com, (vport->phba->fc_ratov-1));
	bf_set(wqe_class, &wqe->gen_req.wqe_com, CLASS3);
	bf_set(wqe_cmnd, &wqe->gen_req.wqe_com, CMD_GEN_REQUEST64_WQE);
	bf_set(wqe_ct, &wqe->gen_req.wqe_com, SLI4_CT_RPI);

	/* Word 8 */
	wqe->gen_req.wqe_com.abort_tag = genwqe->iotag;

	/* Word 9 */
	bf_set(wqe_reqtag, &wqe->gen_req.wqe_com, genwqe->iotag);

	/* Word 10 */
	bf_set(wqe_dbde, &wqe->gen_req.wqe_com, 1);
	bf_set(wqe_iod, &wqe->gen_req.wqe_com, LPFC_WQE_IOD_READ);
	bf_set(wqe_qosd, &wqe->gen_req.wqe_com, 1);
	bf_set(wqe_lenloc, &wqe->gen_req.wqe_com, LPFC_WQE_LENLOC_NONE);
	bf_set(wqe_ebde_cnt, &wqe->gen_req.wqe_com, 0);

	/* Word 11 */
	bf_set(wqe_cqid, &wqe->gen_req.wqe_com, LPFC_WQE_CQ_ID_DEFAULT);
	bf_set(wqe_cmd_type, &wqe->gen_req.wqe_com, OTHER_COMMAND);


	/* Issue GEN REQ WQE for NPORT <did> */
	lpfc_printf_vlog(vport, KERN_INFO, LOG_ELS,
			 "6050 Issue GEN REQ WQE to NPORT x%x "
			 "Data: x%x x%x wq:x%px lsreq:x%px bmp:x%px "
			 "xmit:%d 1st:%d\n",
			 ndlp->nlp_DID, genwqe->iotag,
			 vport->port_state,
			genwqe, pnvme_lsreq, bmp, xmit_len, first_len);
	genwqe->wqe_cmpl = cmpl;
	genwqe->iocb_cmpl = NULL;
	genwqe->drvrTimeout = tmo + LPFC_DRVR_TIMEOUT;
	genwqe->vport = vport;
	genwqe->retry = retry;

	lpfc_nvmeio_data(phba, "NVME LS  XMIT: xri x%x iotag x%x to x%06x\n",
			 genwqe->sli4_xritag, genwqe->iotag, ndlp->nlp_DID);

	rc = lpfc_sli4_issue_wqe(phba, &phba->sli4_hba.hdwq[0], genwqe);
	if (rc) {
		lpfc_printf_vlog(vport, KERN_ERR, LOG_ELS,
				 "6045 Issue GEN REQ WQE to NPORT x%x "
				 "Data: x%x x%x\n",
				 ndlp->nlp_DID, genwqe->iotag,
				 vport->port_state);
		lpfc_sli_release_iocbq(phba, genwqe);
		return 1;
	}
	return 0;
}
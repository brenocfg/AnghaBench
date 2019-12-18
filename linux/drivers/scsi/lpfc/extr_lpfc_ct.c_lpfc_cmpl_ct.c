#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct lpfc_vport {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  CmdRsp; } ;
struct TYPE_7__ {TYPE_1__ bits; } ;
struct lpfc_sli_ct_request {TYPE_2__ CommandResponse; } ;
struct lpfc_nodelist {int dummy; } ;
struct TYPE_9__ {struct lpfc_nodelist* ndlp; struct lpfc_iocbq* rsp_iocb; } ;
struct TYPE_8__ {int* ulpWord; } ;
struct TYPE_10__ {scalar_t__ ulpStatus; TYPE_3__ un; int /*<<< orphan*/  ulpIoTag; int /*<<< orphan*/  ulpContext; } ;
struct lpfc_iocbq {scalar_t__ retry; TYPE_4__ context_un; TYPE_5__ iocb; scalar_t__ context2; scalar_t__ context1; struct lpfc_vport* vport; } ;
struct lpfc_hba {int dummy; } ;
struct lpfc_dmabuf {scalar_t__ virt; } ;
typedef  TYPE_5__ IOCB_t ;

/* Variables and functions */
 int IOERR_PARAM_MASK ; 
 int IOERR_SLI_ABORTED ; 
 int IOERR_SLI_DOWN ; 
 scalar_t__ IOSTAT_LOCAL_REJECT ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  LOG_DISCOVERY ; 
 int /*<<< orphan*/  LPFC_DISC_TRC_CT ; 
 scalar_t__ LPFC_MAX_NS_RETRY ; 
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_ct_free_iocb (struct lpfc_hba*,struct lpfc_iocbq*) ; 
 int /*<<< orphan*/  lpfc_debugfs_disc_trc (struct lpfc_vport*,int /*<<< orphan*/ ,char*,scalar_t__,int,int) ; 
 int /*<<< orphan*/  lpfc_els_chk_latt (struct lpfc_vport*) ; 
 int lpfc_ns_cmd (struct lpfc_vport*,int,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_printf_vlog (struct lpfc_vport*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,...) ; 

__attribute__((used)) static void
lpfc_cmpl_ct(struct lpfc_hba *phba, struct lpfc_iocbq *cmdiocb,
	     struct lpfc_iocbq *rspiocb)
{
	struct lpfc_vport *vport = cmdiocb->vport;
	struct lpfc_dmabuf *inp;
	struct lpfc_dmabuf *outp;
	IOCB_t *irsp;
	struct lpfc_sli_ct_request *CTrsp;
	struct lpfc_nodelist *ndlp;
	int cmdcode, rc;
	uint8_t retry;
	uint32_t latt;

	/* First save ndlp, before we overwrite it */
	ndlp = cmdiocb->context_un.ndlp;

	/* we pass cmdiocb to state machine which needs rspiocb as well */
	cmdiocb->context_un.rsp_iocb = rspiocb;

	inp = (struct lpfc_dmabuf *) cmdiocb->context1;
	outp = (struct lpfc_dmabuf *) cmdiocb->context2;
	irsp = &rspiocb->iocb;

	cmdcode = be16_to_cpu(((struct lpfc_sli_ct_request *) inp->virt)->
					CommandResponse.bits.CmdRsp);
	CTrsp = (struct lpfc_sli_ct_request *) outp->virt;

	latt = lpfc_els_chk_latt(vport);

	/* RFT request completes status <ulpStatus> CmdRsp <CmdRsp> */
	lpfc_printf_vlog(vport, KERN_INFO, LOG_DISCOVERY,
			 "0209 CT Request completes, latt %d, "
			 "ulpStatus x%x CmdRsp x%x, Context x%x, Tag x%x\n",
			 latt, irsp->ulpStatus,
			 CTrsp->CommandResponse.bits.CmdRsp,
			 cmdiocb->iocb.ulpContext, cmdiocb->iocb.ulpIoTag);

	lpfc_debugfs_disc_trc(vport, LPFC_DISC_TRC_CT,
		"CT cmd cmpl:     status:x%x/x%x cmd:x%x",
		irsp->ulpStatus, irsp->un.ulpWord[4], cmdcode);

	if (irsp->ulpStatus) {
		lpfc_printf_vlog(vport, KERN_ERR, LOG_DISCOVERY,
				 "0268 NS cmd x%x Error (x%x x%x)\n",
				 cmdcode, irsp->ulpStatus, irsp->un.ulpWord[4]);

		if ((irsp->ulpStatus == IOSTAT_LOCAL_REJECT) &&
			(((irsp->un.ulpWord[4] & IOERR_PARAM_MASK) ==
			  IOERR_SLI_DOWN) ||
			 ((irsp->un.ulpWord[4] & IOERR_PARAM_MASK) ==
			  IOERR_SLI_ABORTED)))
			goto out;

		retry = cmdiocb->retry;
		if (retry >= LPFC_MAX_NS_RETRY)
			goto out;

		retry++;
		lpfc_printf_vlog(vport, KERN_INFO, LOG_DISCOVERY,
				 "0250 Retrying NS cmd %x\n", cmdcode);
		rc = lpfc_ns_cmd(vport, cmdcode, retry, 0);
		if (rc == 0)
			goto out;
	}

out:
	cmdiocb->context_un.ndlp = ndlp; /* Now restore ndlp for free */
	lpfc_ct_free_iocb(phba, cmdiocb);
	return;
}
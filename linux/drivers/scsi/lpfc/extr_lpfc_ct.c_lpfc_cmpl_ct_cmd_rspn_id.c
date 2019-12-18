#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct lpfc_vport {int /*<<< orphan*/  ct_flags; } ;
struct TYPE_4__ {scalar_t__ CmdRsp; } ;
struct TYPE_5__ {TYPE_1__ bits; } ;
struct lpfc_sli_ct_request {TYPE_2__ CommandResponse; } ;
struct TYPE_6__ {scalar_t__ ulpStatus; } ;
struct lpfc_iocbq {scalar_t__ context2; struct lpfc_vport* vport; TYPE_3__ iocb; } ;
struct lpfc_hba {int dummy; } ;
struct lpfc_dmabuf {scalar_t__ virt; } ;
typedef  TYPE_3__ IOCB_t ;

/* Variables and functions */
 int /*<<< orphan*/  FC_CT_RSPN_ID ; 
 scalar_t__ IOSTAT_SUCCESS ; 
 int /*<<< orphan*/  SLI_CT_RESPONSE_FS_ACC ; 
 scalar_t__ be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_cmpl_ct (struct lpfc_hba*,struct lpfc_iocbq*,struct lpfc_iocbq*) ; 

__attribute__((used)) static void
lpfc_cmpl_ct_cmd_rspn_id(struct lpfc_hba *phba, struct lpfc_iocbq *cmdiocb,
			 struct lpfc_iocbq *rspiocb)
{
	IOCB_t *irsp = &rspiocb->iocb;
	struct lpfc_vport *vport = cmdiocb->vport;

	if (irsp->ulpStatus == IOSTAT_SUCCESS) {
		struct lpfc_dmabuf *outp;
		struct lpfc_sli_ct_request *CTrsp;

		outp = (struct lpfc_dmabuf *) cmdiocb->context2;
		CTrsp = (struct lpfc_sli_ct_request *) outp->virt;
		if (CTrsp->CommandResponse.bits.CmdRsp ==
		    be16_to_cpu(SLI_CT_RESPONSE_FS_ACC))
			vport->ct_flags |= FC_CT_RSPN_ID;
	}
	lpfc_cmpl_ct(phba, cmdiocb, rspiocb);
	return;
}
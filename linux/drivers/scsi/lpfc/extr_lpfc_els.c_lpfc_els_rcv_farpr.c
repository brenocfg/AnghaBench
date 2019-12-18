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
typedef  int /*<<< orphan*/  uint32_t ;
struct lpfc_vport {int dummy; } ;
struct lpfc_nodelist {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  remoteID; } ;
struct TYPE_5__ {TYPE_1__ elsreq64; } ;
struct TYPE_6__ {TYPE_2__ un; } ;
struct lpfc_iocbq {scalar_t__ context2; TYPE_3__ iocb; } ;
struct lpfc_dmabuf {scalar_t__ virt; } ;
typedef  TYPE_3__ IOCB_t ;

/* Variables and functions */
 int /*<<< orphan*/  ELS_CMD_ACC ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  LOG_ELS ; 
 int /*<<< orphan*/  lpfc_els_rsp_acc (struct lpfc_vport*,int /*<<< orphan*/ ,struct lpfc_iocbq*,struct lpfc_nodelist*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lpfc_printf_vlog (struct lpfc_vport*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
lpfc_els_rcv_farpr(struct lpfc_vport *vport, struct lpfc_iocbq *cmdiocb,
		   struct lpfc_nodelist  *ndlp)
{
	struct lpfc_dmabuf *pcmd;
	uint32_t *lp;
	IOCB_t *icmd;
	uint32_t did;

	icmd = &cmdiocb->iocb;
	did = icmd->un.elsreq64.remoteID;
	pcmd = (struct lpfc_dmabuf *) cmdiocb->context2;
	lp = (uint32_t *) pcmd->virt;

	lp++;
	/* FARP-RSP received from DID <did> */
	lpfc_printf_vlog(vport, KERN_INFO, LOG_ELS,
			 "0600 FARP-RSP received from DID x%x\n", did);
	/* ACCEPT the Farp resp request */
	lpfc_els_rsp_acc(vport, ELS_CMD_ACC, cmdiocb, ndlp, NULL);

	return 0;
}
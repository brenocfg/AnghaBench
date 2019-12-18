#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct lpfc_vport {int dummy; } ;
struct lpfc_nodelist {int dummy; } ;
struct lpfc_iocbq {scalar_t__ drvrTimeout; } ;
struct lpfc_hba {int /*<<< orphan*/  mbox_mem_pool; } ;
struct TYPE_4__ {struct lpfc_vport* vport; scalar_t__ ctx_ndlp; scalar_t__ ctx_buf; } ;
typedef  TYPE_1__ LPFC_MBOXQ_t ;

/* Variables and functions */
 scalar_t__ ELS_CMD_ADISC ; 
 int /*<<< orphan*/  ELS_CMD_PLOGI ; 
 int /*<<< orphan*/  kfree (struct lpfc_iocbq*) ; 
 int /*<<< orphan*/  lpfc_els_rsp_acc (struct lpfc_vport*,int /*<<< orphan*/ ,struct lpfc_iocbq*,struct lpfc_nodelist*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lpfc_els_rsp_adisc_acc (struct lpfc_vport*,struct lpfc_iocbq*,struct lpfc_nodelist*) ; 
 int /*<<< orphan*/  mempool_free (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
lpfc_mbx_cmpl_resume_rpi(struct lpfc_hba *phba, LPFC_MBOXQ_t *mboxq)
{
	struct lpfc_vport *vport;
	struct lpfc_iocbq *elsiocb;
	struct lpfc_nodelist *ndlp;
	uint32_t cmd;

	elsiocb = (struct lpfc_iocbq *)mboxq->ctx_buf;
	ndlp = (struct lpfc_nodelist *)mboxq->ctx_ndlp;
	vport = mboxq->vport;
	cmd = elsiocb->drvrTimeout;

	if (cmd == ELS_CMD_ADISC) {
		lpfc_els_rsp_adisc_acc(vport, elsiocb, ndlp);
	} else {
		lpfc_els_rsp_acc(vport, ELS_CMD_PLOGI, elsiocb,
			ndlp, NULL);
	}
	kfree(elsiocb);
	mempool_free(mboxq, phba->mbox_mem_pool);
}
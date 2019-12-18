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
struct TYPE_5__ {int /*<<< orphan*/  lsRjtRsnCodeExp; int /*<<< orphan*/  lsRjtRsnCode; } ;
struct TYPE_6__ {int /*<<< orphan*/  lsRjtError; TYPE_2__ b; } ;
struct ls_rjt {TYPE_3__ un; } ;
struct lpfc_vport {TYPE_1__* phba; } ;
struct lpfc_nodelist {int nlp_flag; int /*<<< orphan*/  nlp_state; } ;
struct lpfc_iocbq {int dummy; } ;
struct TYPE_4__ {scalar_t__ nvmet_support; } ;

/* Variables and functions */
 int /*<<< orphan*/  LSEXP_NOTHING_MORE ; 
 int /*<<< orphan*/  LSRJT_LOGICAL_BSY ; 
 int NLP_RPI_REGISTERED ; 
 int /*<<< orphan*/  lpfc_els_rsp_prli_acc (struct lpfc_vport*,struct lpfc_iocbq*,struct lpfc_nodelist*) ; 
 int /*<<< orphan*/  lpfc_els_rsp_reject (struct lpfc_vport*,int /*<<< orphan*/ ,struct lpfc_iocbq*,struct lpfc_nodelist*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lpfc_rcv_prli (struct lpfc_vport*,struct lpfc_nodelist*,struct lpfc_iocbq*) ; 
 int /*<<< orphan*/  lpfc_rcv_prli_support_check (struct lpfc_vport*,struct lpfc_nodelist*,struct lpfc_iocbq*) ; 
 int /*<<< orphan*/  memset (struct ls_rjt*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static uint32_t
lpfc_rcv_prli_reglogin_issue(struct lpfc_vport *vport,
			     struct lpfc_nodelist *ndlp,
			     void *arg,
			     uint32_t evt)
{
	struct lpfc_iocbq *cmdiocb = (struct lpfc_iocbq *) arg;
	struct ls_rjt     stat;

	if (!lpfc_rcv_prli_support_check(vport, ndlp, cmdiocb)) {
		return ndlp->nlp_state;
	}
	if (vport->phba->nvmet_support) {
		/* NVME Target mode.  Handle and respond to the PRLI and
		 * transition to UNMAPPED provided the RPI has completed
		 * registration.
		 */
		if (ndlp->nlp_flag & NLP_RPI_REGISTERED) {
			lpfc_rcv_prli(vport, ndlp, cmdiocb);
			lpfc_els_rsp_prli_acc(vport, cmdiocb, ndlp);
		} else {
			/* RPI registration has not completed. Reject the PRLI
			 * to prevent an illegal state transition when the
			 * rpi registration does complete.
			 */
			memset(&stat, 0, sizeof(struct ls_rjt));
			stat.un.b.lsRjtRsnCode = LSRJT_LOGICAL_BSY;
			stat.un.b.lsRjtRsnCodeExp = LSEXP_NOTHING_MORE;
			lpfc_els_rsp_reject(vport, stat.un.lsRjtError, cmdiocb,
					    ndlp, NULL);
			return ndlp->nlp_state;
		}
	} else {
		/* Initiator mode. */
		lpfc_els_rsp_prli_acc(vport, cmdiocb, ndlp);
	}
	return ndlp->nlp_state;
}
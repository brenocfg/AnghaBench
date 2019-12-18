#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct lpfc_vport {int dummy; } ;
struct lpfc_nodelist {int /*<<< orphan*/  nlp_state; } ;
struct lpfc_iocbq {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  lpfc_els_rsp_prli_acc (struct lpfc_vport*,struct lpfc_iocbq*,struct lpfc_nodelist*) ; 
 int /*<<< orphan*/  lpfc_rcv_prli_support_check (struct lpfc_vport*,struct lpfc_nodelist*,struct lpfc_iocbq*) ; 

__attribute__((used)) static uint32_t
lpfc_rcv_prli_prli_issue(struct lpfc_vport *vport, struct lpfc_nodelist *ndlp,
			 void *arg, uint32_t evt)
{
	struct lpfc_iocbq *cmdiocb = (struct lpfc_iocbq *) arg;

	if (!lpfc_rcv_prli_support_check(vport, ndlp, cmdiocb))
		return ndlp->nlp_state;
	lpfc_els_rsp_prli_acc(vport, cmdiocb, ndlp);
	return ndlp->nlp_state;
}
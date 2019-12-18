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
struct lpfc_nodelist {int nlp_flag; int /*<<< orphan*/  nlp_state; int /*<<< orphan*/  nlp_DID; void* nlp_prev_state; } ;
struct lpfc_iocbq {int dummy; } ;

/* Variables and functions */
 int NLP_DELAY_TMO ; 
 int NLP_NPR_2B_DISC ; 
 int NLP_NPR_ADISC ; 
 int /*<<< orphan*/  NLP_STE_ADISC_ISSUE ; 
 void* NLP_STE_NPR_NODE ; 
 int /*<<< orphan*/  NLP_STE_PLOGI_ISSUE ; 
 int /*<<< orphan*/  lpfc_issue_els_adisc (struct lpfc_vport*,struct lpfc_nodelist*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_issue_els_plogi (struct lpfc_vport*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_nlp_set_state (struct lpfc_vport*,struct lpfc_nodelist*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_rcv_padisc (struct lpfc_vport*,struct lpfc_nodelist*,struct lpfc_iocbq*) ; 

__attribute__((used)) static uint32_t
lpfc_rcv_padisc_npr_node(struct lpfc_vport *vport, struct lpfc_nodelist *ndlp,
			 void *arg, uint32_t evt)
{
	struct lpfc_iocbq *cmdiocb = (struct lpfc_iocbq *) arg;

	lpfc_rcv_padisc(vport, ndlp, cmdiocb);
	/*
	 * Do not start discovery if discovery is about to start
	 * or discovery in progress for this node. Starting discovery
	 * here will affect the counting of discovery threads.
	 */
	if (!(ndlp->nlp_flag & NLP_DELAY_TMO) &&
	    !(ndlp->nlp_flag & NLP_NPR_2B_DISC)) {
		if (ndlp->nlp_flag & NLP_NPR_ADISC) {
			ndlp->nlp_flag &= ~NLP_NPR_ADISC;
			ndlp->nlp_prev_state = NLP_STE_NPR_NODE;
			lpfc_nlp_set_state(vport, ndlp, NLP_STE_ADISC_ISSUE);
			lpfc_issue_els_adisc(vport, ndlp, 0);
		} else {
			ndlp->nlp_prev_state = NLP_STE_NPR_NODE;
			lpfc_nlp_set_state(vport, ndlp, NLP_STE_PLOGI_ISSUE);
			lpfc_issue_els_plogi(vport, ndlp->nlp_DID, 0);
		}
	}
	return ndlp->nlp_state;
}
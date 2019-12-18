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
struct lpfc_vport {int dummy; } ;
struct lpfc_nodelist {scalar_t__ nlp_state; int /*<<< orphan*/  nlp_listp; } ;

/* Variables and functions */
 int /*<<< orphan*/  NLP_STE_UNUSED_NODE ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lpfc_cancel_retry_delay_tmo (struct lpfc_vport*,struct lpfc_nodelist*) ; 
 int /*<<< orphan*/  lpfc_nlp_counters (struct lpfc_vport*,scalar_t__,int) ; 
 int /*<<< orphan*/  lpfc_nlp_state_cleanup (struct lpfc_vport*,struct lpfc_nodelist*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
lpfc_disable_node(struct lpfc_vport *vport, struct lpfc_nodelist *ndlp)
{
	lpfc_cancel_retry_delay_tmo(vport, ndlp);
	if (ndlp->nlp_state && !list_empty(&ndlp->nlp_listp))
		lpfc_nlp_counters(vport, ndlp->nlp_state, -1);
	lpfc_nlp_state_cleanup(vport, ndlp, ndlp->nlp_state,
				NLP_STE_UNUSED_NODE);
}
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
struct lpfc_nodelist {int nlp_flag; int /*<<< orphan*/  nlp_state; int /*<<< orphan*/  nlp_rpi; int /*<<< orphan*/  nlp_DID; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  LOG_DISCOVERY ; 
 int NLP_RCV_PLOGI ; 
 int /*<<< orphan*/  lpfc_printf_vlog (struct lpfc_vport*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static uint32_t
lpfc_cmpl_plogi_illegal(struct lpfc_vport *vport, struct lpfc_nodelist *ndlp,
		  void *arg, uint32_t evt)
{
	/* This transition is only legal if we previously
	 * rcv'ed a PLOGI. Since we don't want 2 discovery threads
	 * working on the same NPortID, do nothing for this thread
	 * to stop it.
	 */
	if (!(ndlp->nlp_flag & NLP_RCV_PLOGI)) {
		lpfc_printf_vlog(vport, KERN_ERR, LOG_DISCOVERY,
			 "0272 Illegal State Transition: node x%x "
			 "event x%x, state x%x Data: x%x x%x\n",
			 ndlp->nlp_DID, evt, ndlp->nlp_state, ndlp->nlp_rpi,
			 ndlp->nlp_flag);
	}
	return ndlp->nlp_state;
}
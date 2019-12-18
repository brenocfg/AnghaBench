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
struct lpfc_vport {int /*<<< orphan*/  phba; } ;
struct lpfc_nodelist {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NLP_STE_FREED_NODE ; 
 int /*<<< orphan*/  lpfc_drop_node (struct lpfc_vport*,struct lpfc_nodelist*) ; 
 int /*<<< orphan*/  lpfc_els_abort (int /*<<< orphan*/ ,struct lpfc_nodelist*) ; 
 int /*<<< orphan*/  lpfc_unreg_rpi (struct lpfc_vport*,struct lpfc_nodelist*) ; 

__attribute__((used)) static uint32_t
lpfc_device_rm_logo_issue(struct lpfc_vport *vport, struct lpfc_nodelist *ndlp,
			  void *arg, uint32_t evt)
{
	/*
	 * DevLoss has timed out and is calling for Device Remove.
	 * In this case, abort the LOGO and cleanup the ndlp
	 */

	lpfc_unreg_rpi(vport, ndlp);
	/* software abort outstanding PLOGI */
	lpfc_els_abort(vport->phba, ndlp);
	lpfc_drop_node(vport, ndlp);
	return NLP_STE_FREED_NODE;
}
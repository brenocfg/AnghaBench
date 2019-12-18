#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  cq_ecount; int /*<<< orphan*/  cq_esize; int /*<<< orphan*/  eq_ecount; int /*<<< orphan*/  eq_esize; } ;
struct lpfc_hba {scalar_t__ cfg_irq_chann; scalar_t__ cfg_nvmet_mrq; TYPE_1__ sli4_hba; int /*<<< orphan*/  cfg_hdw_queue; scalar_t__ nvmet_support; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  LOG_INIT ; 
 int /*<<< orphan*/  LPFC_CQE_DEF_COUNT ; 
 int /*<<< orphan*/  LPFC_CQE_SIZE ; 
 int /*<<< orphan*/  LPFC_EQE_DEF_COUNT ; 
 int /*<<< orphan*/  LPFC_EQE_SIZE_4B ; 
 scalar_t__ LPFC_NVMET_MRQ_MAX ; 
 int /*<<< orphan*/  lpfc_printf_log (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int
lpfc_sli4_queue_verify(struct lpfc_hba *phba)
{
	/*
	 * Sanity check for configured queue parameters against the run-time
	 * device parameters
	 */

	if (phba->nvmet_support) {
		if (phba->cfg_irq_chann < phba->cfg_nvmet_mrq)
			phba->cfg_nvmet_mrq = phba->cfg_irq_chann;
		if (phba->cfg_nvmet_mrq > LPFC_NVMET_MRQ_MAX)
			phba->cfg_nvmet_mrq = LPFC_NVMET_MRQ_MAX;
	}

	lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
			"2574 IO channels: hdwQ %d IRQ %d MRQ: %d\n",
			phba->cfg_hdw_queue, phba->cfg_irq_chann,
			phba->cfg_nvmet_mrq);

	/* Get EQ depth from module parameter, fake the default for now */
	phba->sli4_hba.eq_esize = LPFC_EQE_SIZE_4B;
	phba->sli4_hba.eq_ecount = LPFC_EQE_DEF_COUNT;

	/* Get CQ depth from module parameter, fake the default for now */
	phba->sli4_hba.cq_esize = LPFC_CQE_SIZE;
	phba->sli4_hba.cq_ecount = LPFC_CQE_DEF_COUNT;
	return 0;
}
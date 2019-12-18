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
struct TYPE_2__ {scalar_t__ num_present_cpu; } ;
struct lpfc_hba {scalar_t__ cfg_hdw_queue; scalar_t__ cfg_irq_chann; int cfg_enable_fc4_type; scalar_t__ cfg_nvme_enable_fb; scalar_t__ cfg_nvmet_fb_size; scalar_t__ cfg_nvmet_mrq; scalar_t__ nvmet_support; TYPE_1__ sli4_hba; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  LOG_NVME_DISC ; 
 int LPFC_ENABLE_FCP ; 
 int LPFC_ENABLE_NVME ; 
 scalar_t__ LPFC_NVMET_FB_SZ_MAX ; 
 scalar_t__ LPFC_NVMET_MRQ_MAX ; 
 int /*<<< orphan*/  lpfc_printf_log (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__,...) ; 

void
lpfc_nvme_mod_param_dep(struct lpfc_hba *phba)
{
	if (phba->cfg_hdw_queue > phba->sli4_hba.num_present_cpu)
		phba->cfg_hdw_queue = phba->sli4_hba.num_present_cpu;
	if (phba->cfg_irq_chann > phba->sli4_hba.num_present_cpu)
		phba->cfg_irq_chann = phba->sli4_hba.num_present_cpu;
	if (phba->cfg_irq_chann > phba->cfg_hdw_queue)
		phba->cfg_irq_chann = phba->cfg_hdw_queue;

	if (phba->cfg_enable_fc4_type & LPFC_ENABLE_NVME &&
	    phba->nvmet_support) {
		phba->cfg_enable_fc4_type &= ~LPFC_ENABLE_FCP;

		lpfc_printf_log(phba, KERN_INFO, LOG_NVME_DISC,
				"6013 %s x%x fb_size x%x, fb_max x%x\n",
				"NVME Target PRLI ACC enable_fb ",
				phba->cfg_nvme_enable_fb,
				phba->cfg_nvmet_fb_size,
				LPFC_NVMET_FB_SZ_MAX);

		if (phba->cfg_nvme_enable_fb == 0)
			phba->cfg_nvmet_fb_size = 0;
		else {
			if (phba->cfg_nvmet_fb_size > LPFC_NVMET_FB_SZ_MAX)
				phba->cfg_nvmet_fb_size = LPFC_NVMET_FB_SZ_MAX;
		}

		if (!phba->cfg_nvmet_mrq)
			phba->cfg_nvmet_mrq = phba->cfg_irq_chann;

		/* Adjust lpfc_nvmet_mrq to avoid running out of WQE slots */
		if (phba->cfg_nvmet_mrq > phba->cfg_irq_chann) {
			phba->cfg_nvmet_mrq = phba->cfg_irq_chann;
			lpfc_printf_log(phba, KERN_ERR, LOG_NVME_DISC,
					"6018 Adjust lpfc_nvmet_mrq to %d\n",
					phba->cfg_nvmet_mrq);
		}
		if (phba->cfg_nvmet_mrq > LPFC_NVMET_MRQ_MAX)
			phba->cfg_nvmet_mrq = LPFC_NVMET_MRQ_MAX;

	} else {
		/* Not NVME Target mode.  Turn off Target parameters. */
		phba->nvmet_support = 0;
		phba->cfg_nvmet_mrq = 0;
		phba->cfg_nvmet_fb_size = 0;
	}
}
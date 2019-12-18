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
struct lpfc_ras_fwlog {int ras_active; } ;
struct TYPE_2__ {scalar_t__ conf_regs_memmap_p; } ;
struct lpfc_hba {TYPE_1__ sli4_hba; struct lpfc_ras_fwlog ras_fwlog; } ;

/* Variables and functions */
 int /*<<< orphan*/  LPFC_CTL_PDEV_CTL_DDL_RAS ; 
 scalar_t__ LPFC_CTL_PDEV_CTL_OFFSET ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

void
lpfc_ras_stop_fwlog(struct lpfc_hba *phba)
{
	struct lpfc_ras_fwlog *ras_fwlog = &phba->ras_fwlog;

	ras_fwlog->ras_active = false;

	/* Disable FW logging to host memory */
	writel(LPFC_CTL_PDEV_CTL_DDL_RAS,
	       phba->sli4_hba.conf_regs_memmap_p + LPFC_CTL_PDEV_CTL_OFFSET);
}
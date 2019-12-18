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
struct lpfc_sli {int /*<<< orphan*/  sli_flag; } ;
struct lpfc_hba {scalar_t__ sli_rev; int /*<<< orphan*/  hbalock; int /*<<< orphan*/  HCregaddr; struct lpfc_sli sli; } ;

/* Variables and functions */
 int /*<<< orphan*/  HC_LAINT_ENA ; 
 int /*<<< orphan*/  LPFC_PROCESS_LA ; 
 scalar_t__ LPFC_SLI_REV3 ; 
 int /*<<< orphan*/  readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
lpfc_enable_la(struct lpfc_hba *phba)
{
	uint32_t control;
	struct lpfc_sli *psli = &phba->sli;
	spin_lock_irq(&phba->hbalock);
	psli->sli_flag |= LPFC_PROCESS_LA;
	if (phba->sli_rev <= LPFC_SLI_REV3) {
		control = readl(phba->HCregaddr);
		control |= HC_LAINT_ENA;
		writel(control, phba->HCregaddr);
		readl(phba->HCregaddr); /* flush */
	}
	spin_unlock_irq(&phba->hbalock);
}
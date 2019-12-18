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
typedef  int uint32_t ;
struct lpfc_sli {int /*<<< orphan*/  stats_start; int /*<<< orphan*/  lnk_stat_offsets; int /*<<< orphan*/  sli_flag; } ;
struct lpfc_hba {int hba_flag; int /*<<< orphan*/  pcidev; int /*<<< orphan*/  hbalock; int /*<<< orphan*/  link_state; TYPE_1__* pport; struct lpfc_sli sli; } ;
struct TYPE_2__ {scalar_t__ stopped; int /*<<< orphan*/  port_state; } ;

/* Variables and functions */
 int HBA_AER_ENABLED ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  LOG_SLI ; 
 int /*<<< orphan*/  LPFC_HBA_ERROR ; 
 int /*<<< orphan*/  LPFC_INIT_START ; 
 int /*<<< orphan*/  ktime_get_seconds () ; 
 int /*<<< orphan*/  lpfc_hba_down_post (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_printf_log (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int lpfc_sli4_brdreset (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_sli4_queue_destroy (struct lpfc_hba*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_disable_pcie_error_reporting (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
lpfc_sli_brdrestart_s4(struct lpfc_hba *phba)
{
	struct lpfc_sli *psli = &phba->sli;
	uint32_t hba_aer_enabled;
	int rc;

	/* Restart HBA */
	lpfc_printf_log(phba, KERN_INFO, LOG_SLI,
			"0296 Restart HBA Data: x%x x%x\n",
			phba->pport->port_state, psli->sli_flag);

	/* Take PCIe device Advanced Error Reporting (AER) state */
	hba_aer_enabled = phba->hba_flag & HBA_AER_ENABLED;

	rc = lpfc_sli4_brdreset(phba);
	if (rc) {
		phba->link_state = LPFC_HBA_ERROR;
		goto hba_down_queue;
	}

	spin_lock_irq(&phba->hbalock);
	phba->pport->stopped = 0;
	phba->link_state = LPFC_INIT_START;
	phba->hba_flag = 0;
	spin_unlock_irq(&phba->hbalock);

	memset(&psli->lnk_stat_offsets, 0, sizeof(psli->lnk_stat_offsets));
	psli->stats_start = ktime_get_seconds();

	/* Reset HBA AER if it was enabled, note hba_flag was reset above */
	if (hba_aer_enabled)
		pci_disable_pcie_error_reporting(phba->pcidev);

hba_down_queue:
	lpfc_hba_down_post(phba);
	lpfc_sli4_queue_destroy(phba);

	return rc;
}
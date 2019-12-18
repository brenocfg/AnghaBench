#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct TYPE_5__ {scalar_t__ cmdidx; scalar_t__ local_getidx; scalar_t__ next_cmdidx; scalar_t__ rspidx; } ;
struct TYPE_6__ {TYPE_2__ sli3; } ;
struct lpfc_sli_ring {scalar_t__ missbufcnt; TYPE_3__ sli; scalar_t__ flag; } ;
struct lpfc_sli {int sli_flag; int num_rings; struct lpfc_sli_ring* sli3_ring; } ;
struct lpfc_hba {int /*<<< orphan*/  link_state; int /*<<< orphan*/  pcidev; int /*<<< orphan*/  HCregaddr; TYPE_1__* pport; scalar_t__ link_events; scalar_t__ fc_eventTag; struct lpfc_sli sli; } ;
struct TYPE_4__ {scalar_t__ fc_prevDID; scalar_t__ fc_myDID; int /*<<< orphan*/  port_state; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  HC_INITFF ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  LOG_SLI ; 
 int LPFC_PROCESS_LA ; 
 int LPFC_SLI_ACTIVE ; 
 int /*<<< orphan*/  LPFC_WARM_START ; 
 int /*<<< orphan*/  PCI_COMMAND ; 
 int PCI_COMMAND_PARITY ; 
 int PCI_COMMAND_SERR ; 
 int /*<<< orphan*/  lpfc_printf_log (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 scalar_t__ pci_read_config_word (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_write_config_word (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
lpfc_sli_brdreset(struct lpfc_hba *phba)
{
	struct lpfc_sli *psli;
	struct lpfc_sli_ring *pring;
	uint16_t cfg_value;
	int i;

	psli = &phba->sli;

	/* Reset HBA */
	lpfc_printf_log(phba, KERN_INFO, LOG_SLI,
			"0325 Reset HBA Data: x%x x%x\n",
			(phba->pport) ? phba->pport->port_state : 0,
			psli->sli_flag);

	/* perform board reset */
	phba->fc_eventTag = 0;
	phba->link_events = 0;
	if (phba->pport) {
		phba->pport->fc_myDID = 0;
		phba->pport->fc_prevDID = 0;
	}

	/* Turn off parity checking and serr during the physical reset */
	if (pci_read_config_word(phba->pcidev, PCI_COMMAND, &cfg_value))
		return -EIO;

	pci_write_config_word(phba->pcidev, PCI_COMMAND,
			      (cfg_value &
			       ~(PCI_COMMAND_PARITY | PCI_COMMAND_SERR)));

	psli->sli_flag &= ~(LPFC_SLI_ACTIVE | LPFC_PROCESS_LA);

	/* Now toggle INITFF bit in the Host Control Register */
	writel(HC_INITFF, phba->HCregaddr);
	mdelay(1);
	readl(phba->HCregaddr); /* flush */
	writel(0, phba->HCregaddr);
	readl(phba->HCregaddr); /* flush */

	/* Restore PCI cmd register */
	pci_write_config_word(phba->pcidev, PCI_COMMAND, cfg_value);

	/* Initialize relevant SLI info */
	for (i = 0; i < psli->num_rings; i++) {
		pring = &psli->sli3_ring[i];
		pring->flag = 0;
		pring->sli.sli3.rspidx = 0;
		pring->sli.sli3.next_cmdidx  = 0;
		pring->sli.sli3.local_getidx = 0;
		pring->sli.sli3.cmdidx = 0;
		pring->missbufcnt = 0;
	}

	phba->link_state = LPFC_WARM_START;
	return 0;
}
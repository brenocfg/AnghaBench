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
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct lpfc_hba {scalar_t__ brd_no; int /*<<< orphan*/  ct_ev_waiters; int /*<<< orphan*/  ct_ev_lock; int /*<<< orphan*/  eratt_poll_interval; struct pci_dev* pcidev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LPFC_ERATT_POLL_INTERVAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  kfree (struct lpfc_hba*) ; 
 struct lpfc_hba* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ lpfc_get_instance () ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct lpfc_hba *
lpfc_hba_alloc(struct pci_dev *pdev)
{
	struct lpfc_hba *phba;

	/* Allocate memory for HBA structure */
	phba = kzalloc(sizeof(struct lpfc_hba), GFP_KERNEL);
	if (!phba) {
		dev_err(&pdev->dev, "failed to allocate hba struct\n");
		return NULL;
	}

	/* Set reference to PCI device in HBA structure */
	phba->pcidev = pdev;

	/* Assign an unused board number */
	phba->brd_no = lpfc_get_instance();
	if (phba->brd_no < 0) {
		kfree(phba);
		return NULL;
	}
	phba->eratt_poll_interval = LPFC_ERATT_POLL_INTERVAL;

	spin_lock_init(&phba->ct_ev_lock);
	INIT_LIST_HEAD(&phba->ct_ev_waiters);

	return phba;
}
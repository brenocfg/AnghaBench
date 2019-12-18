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
struct csio_hw {int /*<<< orphan*/  lock; int /*<<< orphan*/  sm; } ;
typedef  int /*<<< orphan*/  pci_ers_result_t ;

/* Variables and functions */
 int /*<<< orphan*/  CSIO_HWE_PCIERR_SLOT_RESET ; 
 int /*<<< orphan*/  PCI_ERS_RESULT_DISCONNECT ; 
 int /*<<< orphan*/  PCI_ERS_RESULT_RECOVERED ; 
 int csio_is_hw_ready (struct csio_hw*) ; 
 int /*<<< orphan*/  csio_post_event (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ pci_enable_device (struct pci_dev*) ; 
 struct csio_hw* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_restore_state (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_save_state (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_master (struct pci_dev*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static pci_ers_result_t
csio_pci_slot_reset(struct pci_dev *pdev)
{
	struct csio_hw *hw = pci_get_drvdata(pdev);
	int ready;

	if (pci_enable_device(pdev)) {
		dev_err(&pdev->dev, "cannot re-enable device in slot reset\n");
		return PCI_ERS_RESULT_DISCONNECT;
	}

	pci_set_master(pdev);
	pci_restore_state(pdev);
	pci_save_state(pdev);

	/* Bring HW s/m to ready state.
	 * but don't resume IOs.
	 */
	spin_lock_irq(&hw->lock);
	csio_post_event(&hw->sm, CSIO_HWE_PCIERR_SLOT_RESET);
	ready = csio_is_hw_ready(hw);
	spin_unlock_irq(&hw->lock);

	if (ready) {
		return PCI_ERS_RESULT_RECOVERED;
	} else {
		dev_err(&pdev->dev, "Can't initialize HW when in slot reset\n");
		return PCI_ERS_RESULT_DISCONNECT;
	}
}
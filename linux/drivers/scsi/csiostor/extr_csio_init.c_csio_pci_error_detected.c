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
struct pci_dev {int dummy; } ;
struct csio_hw {int /*<<< orphan*/  lock; int /*<<< orphan*/  sm; } ;
typedef  int /*<<< orphan*/  pci_ers_result_t ;
typedef  scalar_t__ pci_channel_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  CSIO_HWE_PCIERR_DETECTED ; 
 int /*<<< orphan*/  PCI_ERS_RESULT_DISCONNECT ; 
 int /*<<< orphan*/  PCI_ERS_RESULT_NEED_RESET ; 
 int /*<<< orphan*/  csio_intr_disable (struct csio_hw*,int) ; 
 int /*<<< orphan*/  csio_lnodes_block_request (struct csio_hw*) ; 
 int /*<<< orphan*/  csio_lnodes_exit (struct csio_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csio_lnodes_unblock_request (struct csio_hw*) ; 
 int /*<<< orphan*/  csio_post_event (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ pci_channel_io_perm_failure ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 struct csio_hw* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static pci_ers_result_t
csio_pci_error_detected(struct pci_dev *pdev, pci_channel_state_t state)
{
	struct csio_hw *hw = pci_get_drvdata(pdev);

	csio_lnodes_block_request(hw);
	spin_lock_irq(&hw->lock);

	/* Post PCI error detected evt to HW s/m
	 * HW s/m handles this evt by quiescing IOs, unregisters rports
	 * and finally takes the device to offline.
	 */
	csio_post_event(&hw->sm, CSIO_HWE_PCIERR_DETECTED);
	spin_unlock_irq(&hw->lock);
	csio_lnodes_unblock_request(hw);
	csio_lnodes_exit(hw, 0);
	csio_intr_disable(hw, true);
	pci_disable_device(pdev);
	return state == pci_channel_io_perm_failure ?
		PCI_ERS_RESULT_DISCONNECT : PCI_ERS_RESULT_NEED_RESET;
}
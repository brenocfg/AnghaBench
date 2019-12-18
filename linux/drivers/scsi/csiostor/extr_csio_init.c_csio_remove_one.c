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
struct csio_hw {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  csio_hw_free (struct csio_hw*) ; 
 int /*<<< orphan*/  csio_hw_stop (struct csio_hw*) ; 
 int /*<<< orphan*/  csio_lnodes_block_request (struct csio_hw*) ; 
 int /*<<< orphan*/  csio_lnodes_exit (struct csio_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csio_lnodes_unblock_request (struct csio_hw*) ; 
 int /*<<< orphan*/  csio_pci_exit (struct pci_dev*,int*) ; 
 struct csio_hw* pci_get_drvdata (struct pci_dev*) ; 
 int pci_select_bars (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void csio_remove_one(struct pci_dev *pdev)
{
	struct csio_hw *hw = pci_get_drvdata(pdev);
	int bars = pci_select_bars(pdev, IORESOURCE_MEM);

	csio_lnodes_block_request(hw);
	spin_lock_irq(&hw->lock);

	/* Stops lnode, Rnode s/m
	 * Quiesce IOs.
	 * All sessions with remote ports are unregistered.
	 */
	csio_hw_stop(hw);
	spin_unlock_irq(&hw->lock);
	csio_lnodes_unblock_request(hw);

	csio_lnodes_exit(hw, 0);
	csio_hw_free(hw);
	csio_pci_exit(pdev, &bars);
}
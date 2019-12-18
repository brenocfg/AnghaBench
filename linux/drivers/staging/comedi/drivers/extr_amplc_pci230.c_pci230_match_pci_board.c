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
struct pci_dev {scalar_t__ device; } ;
struct pci230_board {scalar_t__ id; scalar_t__ min_hwver; } ;

/* Variables and functions */
 int pci_resource_len (struct pci_dev*,int) ; 

__attribute__((used)) static bool pci230_match_pci_board(const struct pci230_board *board,
				   struct pci_dev *pci_dev)
{
	/* assume pci_dev->device != PCI_DEVICE_ID_INVALID */
	if (board->id != pci_dev->device)
		return false;
	if (board->min_hwver == 0)
		return true;
	/* Looking for a '+' model.  First check length of registers. */
	if (pci_resource_len(pci_dev, 3) < 32)
		return false;	/* Not a '+' model. */
	/*
	 * TODO: temporarily enable PCI device and read the hardware version
	 * register.  For now, assume it's okay.
	 */
	return true;
}
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
typedef  int u8 ;
typedef  int u16 ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_EXP_DEVSTA ; 
 int PCI_EXP_DEVSTA_TRPND ; 
 int /*<<< orphan*/  pcie_capability_read_word (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 

u8 bnx2x_is_pcie_pending(struct pci_dev *dev)
{
	u16 status;

	pcie_capability_read_word(dev, PCI_EXP_DEVSTA, &status);
	return status & PCI_EXP_DEVSTA_TRPND;
}
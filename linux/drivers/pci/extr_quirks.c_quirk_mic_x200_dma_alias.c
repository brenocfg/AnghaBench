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

/* Variables and functions */
 int /*<<< orphan*/  PCI_DEVFN (int,int) ; 
 int /*<<< orphan*/  pci_add_dma_alias (struct pci_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void quirk_mic_x200_dma_alias(struct pci_dev *pdev)
{
	pci_add_dma_alias(pdev, PCI_DEVFN(0x10, 0x0));
	pci_add_dma_alias(pdev, PCI_DEVFN(0x11, 0x0));
	pci_add_dma_alias(pdev, PCI_DEVFN(0x12, 0x3));
}
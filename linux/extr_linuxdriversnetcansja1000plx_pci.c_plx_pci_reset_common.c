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
typedef  int /*<<< orphan*/  u32 ;
struct plx_pci_card {scalar_t__ conf_addr; } ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 scalar_t__ PLX_CNTRL ; 
 int /*<<< orphan*/  PLX_PCI_RESET ; 
 int /*<<< orphan*/  ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/ ,scalar_t__) ; 
 struct plx_pci_card* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void plx_pci_reset_common(struct pci_dev *pdev)
{
	struct plx_pci_card *card = pci_get_drvdata(pdev);
	u32 cntrl;

	cntrl = ioread32(card->conf_addr + PLX_CNTRL);
	cntrl |= PLX_PCI_RESET;
	iowrite32(cntrl, card->conf_addr + PLX_CNTRL);
	udelay(100);
	cntrl ^= PLX_PCI_RESET;
	iowrite32(cntrl, card->conf_addr + PLX_CNTRL);
}
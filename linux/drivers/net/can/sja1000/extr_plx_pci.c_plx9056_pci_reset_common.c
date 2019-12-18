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
 scalar_t__ PLX9056_CNTRL ; 
 int /*<<< orphan*/  PLX9056_PCI_RCR ; 
 int /*<<< orphan*/  PLX_PCI_RESET ; 
 int /*<<< orphan*/  ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 struct plx_pci_card* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void plx9056_pci_reset_common(struct pci_dev *pdev)
{
	struct plx_pci_card *card = pci_get_drvdata(pdev);
	u32 cntrl;

	/* issue a local bus reset */
	cntrl = ioread32(card->conf_addr + PLX9056_CNTRL);
	cntrl |= PLX_PCI_RESET;
	iowrite32(cntrl, card->conf_addr + PLX9056_CNTRL);
	udelay(100);
	cntrl ^= PLX_PCI_RESET;
	iowrite32(cntrl, card->conf_addr + PLX9056_CNTRL);

	/* reload local configuration from EEPROM */
	cntrl |= PLX9056_PCI_RCR;
	iowrite32(cntrl, card->conf_addr + PLX9056_CNTRL);

	/*
	 * There is no safe way to poll for the end
	 * of reconfiguration process. Waiting for 10ms
	 * is safe.
	 */
	mdelay(10);

	cntrl ^= PLX9056_PCI_RCR;
	iowrite32(cntrl, card->conf_addr + PLX9056_CNTRL);
}
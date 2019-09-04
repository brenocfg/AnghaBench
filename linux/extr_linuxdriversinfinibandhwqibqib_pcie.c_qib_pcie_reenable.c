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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct qib_devdata {int /*<<< orphan*/  pcidev; int /*<<< orphan*/  pcibar1; int /*<<< orphan*/  pcibar0; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_BASE_ADDRESS_0 ; 
 int /*<<< orphan*/  PCI_BASE_ADDRESS_1 ; 
 int /*<<< orphan*/  PCI_CACHE_LINE_SIZE ; 
 int /*<<< orphan*/  PCI_COMMAND ; 
 int /*<<< orphan*/  PCI_INTERRUPT_LINE ; 
 int pci_enable_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_write_config_byte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pci_write_config_dword (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_write_config_word (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qib_dev_err (struct qib_devdata*,char*,int) ; 

void qib_pcie_reenable(struct qib_devdata *dd, u16 cmd, u8 iline, u8 cline)
{
	int r;

	r = pci_write_config_dword(dd->pcidev, PCI_BASE_ADDRESS_0,
				   dd->pcibar0);
	if (r)
		qib_dev_err(dd, "rewrite of BAR0 failed: %d\n", r);
	r = pci_write_config_dword(dd->pcidev, PCI_BASE_ADDRESS_1,
				   dd->pcibar1);
	if (r)
		qib_dev_err(dd, "rewrite of BAR1 failed: %d\n", r);
	/* now re-enable memory access, and restore cosmetic settings */
	pci_write_config_word(dd->pcidev, PCI_COMMAND, cmd);
	pci_write_config_byte(dd->pcidev, PCI_INTERRUPT_LINE, iline);
	pci_write_config_byte(dd->pcidev, PCI_CACHE_LINE_SIZE, cline);
	r = pci_enable_device(dd->pcidev);
	if (r)
		qib_dev_err(dd,
			"pci_enable_device failed after reset: %d\n", r);
}
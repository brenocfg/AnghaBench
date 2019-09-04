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
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_EHCI_FLADJ_REG ; 
 int /*<<< orphan*/  USB_CONFIG ; 
 int /*<<< orphan*/  USB_MSR_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _rdmsr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _wrmsr (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_write_config_dword (struct pci_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void loongson_cs5536_ehci_fixup(struct pci_dev *pdev)
{
	u32 hi, lo;

	/* Serial short detect enable */
	_rdmsr(USB_MSR_REG(USB_CONFIG), &hi, &lo);
	_wrmsr(USB_MSR_REG(USB_CONFIG), (1 << 1) | (1 << 3), lo);

	/* setting the USB2.0 micro frame length */
	pci_write_config_dword(pdev, PCI_EHCI_FLADJ_REG, 0x2000);
}
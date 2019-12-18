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
struct pci_dev {int vendor; scalar_t__ class; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ PCI_CLASS_SERIAL_USB_EHCI ; 
 scalar_t__ PCI_CLASS_SERIAL_USB_OHCI ; 
 scalar_t__ PCI_CLASS_SERIAL_USB_UHCI ; 
 scalar_t__ PCI_CLASS_SERIAL_USB_XHCI ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 scalar_t__ pci_enable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  quirk_usb_disable_ehci (struct pci_dev*) ; 
 int /*<<< orphan*/  quirk_usb_handoff_ohci (struct pci_dev*) ; 
 int /*<<< orphan*/  quirk_usb_handoff_uhci (struct pci_dev*) ; 
 int /*<<< orphan*/  quirk_usb_handoff_xhci (struct pci_dev*) ; 

__attribute__((used)) static void quirk_usb_early_handoff(struct pci_dev *pdev)
{
	/* Skip Netlogic mips SoC's internal PCI USB controller.
	 * This device does not need/support EHCI/OHCI handoff
	 */
	if (pdev->vendor == 0x184e)	/* vendor Netlogic */
		return;
	if (pdev->class != PCI_CLASS_SERIAL_USB_UHCI &&
			pdev->class != PCI_CLASS_SERIAL_USB_OHCI &&
			pdev->class != PCI_CLASS_SERIAL_USB_EHCI &&
			pdev->class != PCI_CLASS_SERIAL_USB_XHCI)
		return;

	if (pci_enable_device(pdev) < 0) {
		dev_warn(&pdev->dev,
			 "Can't enable PCI device, BIOS handoff failed.\n");
		return;
	}
	if (pdev->class == PCI_CLASS_SERIAL_USB_UHCI)
		quirk_usb_handoff_uhci(pdev);
	else if (pdev->class == PCI_CLASS_SERIAL_USB_OHCI)
		quirk_usb_handoff_ohci(pdev);
	else if (pdev->class == PCI_CLASS_SERIAL_USB_EHCI)
		quirk_usb_disable_ehci(pdev);
	else if (pdev->class == PCI_CLASS_SERIAL_USB_XHCI)
		quirk_usb_handoff_xhci(pdev);
	pci_disable_device(pdev);
}
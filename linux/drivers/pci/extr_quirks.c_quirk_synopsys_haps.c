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
struct pci_dev {int device; int /*<<< orphan*/  class; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_CLASS_SERIAL_USB_DEVICE ; 
#define  PCI_DEVICE_ID_SYNOPSYS_HAPSUSB3 130 
#define  PCI_DEVICE_ID_SYNOPSYS_HAPSUSB31 129 
#define  PCI_DEVICE_ID_SYNOPSYS_HAPSUSB3_AXI 128 
 int /*<<< orphan*/  pci_info (struct pci_dev*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void quirk_synopsys_haps(struct pci_dev *pdev)
{
	u32 class = pdev->class;

	switch (pdev->device) {
	case PCI_DEVICE_ID_SYNOPSYS_HAPSUSB3:
	case PCI_DEVICE_ID_SYNOPSYS_HAPSUSB3_AXI:
	case PCI_DEVICE_ID_SYNOPSYS_HAPSUSB31:
		pdev->class = PCI_CLASS_SERIAL_USB_DEVICE;
		pci_info(pdev, "PCI class overridden (%#08x -> %#08x) so dwc3 driver can claim this instead of xhci\n",
			 class, pdev->class);
		break;
	}
}
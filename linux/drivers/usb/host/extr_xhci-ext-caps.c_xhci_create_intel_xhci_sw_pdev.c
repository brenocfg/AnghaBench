#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct xhci_hcd {int dummy; } ;
struct TYPE_3__ {struct device* controller; } ;
struct usb_hcd {scalar_t__ rsrc_start; TYPE_1__ self; } ;
struct resource {int /*<<< orphan*/  flags; int /*<<< orphan*/  name; scalar_t__ start; scalar_t__ end; int /*<<< orphan*/  member_0; } ;
struct TYPE_4__ {struct device* parent; } ;
struct platform_device {TYPE_2__ dev; } ;
struct pci_dev {scalar_t__ device; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ PCI_DEVICE_ID_INTEL_CHERRYVIEW_XHCI ; 
 int /*<<< orphan*/  PLATFORM_DEVID_NONE ; 
 int /*<<< orphan*/  USB_SW_DRV_NAME ; 
 scalar_t__ USB_SW_RESOURCE_SIZE ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int devm_add_action_or_reset (struct device*,int /*<<< orphan*/ ,struct platform_device*) ; 
 int platform_device_add (struct platform_device*) ; 
 int platform_device_add_properties (struct platform_device*,int /*<<< orphan*/ ) ; 
 int platform_device_add_resources (struct platform_device*,struct resource*,int) ; 
 struct platform_device* platform_device_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_device_put (struct platform_device*) ; 
 int /*<<< orphan*/  role_switch_props ; 
 struct pci_dev* to_pci_dev (struct device*) ; 
 int /*<<< orphan*/  xhci_err (struct xhci_hcd*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xhci_intel_unregister_pdev ; 
 struct usb_hcd* xhci_to_hcd (struct xhci_hcd*) ; 

__attribute__((used)) static int xhci_create_intel_xhci_sw_pdev(struct xhci_hcd *xhci, u32 cap_offset)
{
	struct usb_hcd *hcd = xhci_to_hcd(xhci);
	struct device *dev = hcd->self.controller;
	struct platform_device *pdev;
	struct pci_dev *pci = to_pci_dev(dev);
	struct resource	res = { 0, };
	int ret;

	pdev = platform_device_alloc(USB_SW_DRV_NAME, PLATFORM_DEVID_NONE);
	if (!pdev) {
		xhci_err(xhci, "couldn't allocate %s platform device\n",
			 USB_SW_DRV_NAME);
		return -ENOMEM;
	}

	res.start = hcd->rsrc_start + cap_offset;
	res.end	  = res.start + USB_SW_RESOURCE_SIZE - 1;
	res.name  = USB_SW_DRV_NAME;
	res.flags = IORESOURCE_MEM;

	ret = platform_device_add_resources(pdev, &res, 1);
	if (ret) {
		dev_err(dev, "couldn't add resources to intel_xhci_usb_sw pdev\n");
		platform_device_put(pdev);
		return ret;
	}

	if (pci->device == PCI_DEVICE_ID_INTEL_CHERRYVIEW_XHCI) {
		ret = platform_device_add_properties(pdev, role_switch_props);
		if (ret) {
			dev_err(dev, "failed to register device properties\n");
			platform_device_put(pdev);
			return ret;
		}
	}

	pdev->dev.parent = dev;

	ret = platform_device_add(pdev);
	if (ret) {
		dev_err(dev, "couldn't register intel_xhci_usb_sw pdev\n");
		platform_device_put(pdev);
		return ret;
	}

	ret = devm_add_action_or_reset(dev, xhci_intel_unregister_pdev, pdev);
	if (ret) {
		dev_err(dev, "couldn't add unregister action for intel_xhci_usb_sw pdev\n");
		return ret;
	}

	return 0;
}
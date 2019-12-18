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
struct resource {int /*<<< orphan*/  name; int /*<<< orphan*/  flags; } ;
struct property_entry {char* name; } ;
struct TYPE_3__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_1__ dev; } ;
struct dwc3 {scalar_t__ revision; int /*<<< orphan*/  dev; scalar_t__ usb2_lpm_disable; scalar_t__ usb3_lpm_capable; TYPE_2__* xhci_resources; struct platform_device* xhci; } ;
struct TYPE_4__ {int start; int end; int /*<<< orphan*/  name; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct property_entry*) ; 
 scalar_t__ DWC3_REVISION_300A ; 
 int /*<<< orphan*/  DWC3_XHCI_RESOURCES_NUM ; 
 int ENOMEM ; 
 int /*<<< orphan*/  IORESOURCE_IRQ ; 
 int /*<<< orphan*/  PLATFORM_DEVID_AUTO ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int dwc3_host_get_irq (struct dwc3*) ; 
 int /*<<< orphan*/  memset (struct property_entry*,int /*<<< orphan*/ ,int) ; 
 int platform_device_add (struct platform_device*) ; 
 int platform_device_add_properties (struct platform_device*,struct property_entry*) ; 
 int platform_device_add_resources (struct platform_device*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 struct platform_device* platform_device_alloc (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_device_put (struct platform_device*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource_byname (struct platform_device*,int /*<<< orphan*/ ,char*) ; 
 struct platform_device* to_platform_device (int /*<<< orphan*/ ) ; 

int dwc3_host_init(struct dwc3 *dwc)
{
	struct property_entry	props[4];
	struct platform_device	*xhci;
	int			ret, irq;
	struct resource		*res;
	struct platform_device	*dwc3_pdev = to_platform_device(dwc->dev);
	int			prop_idx = 0;

	irq = dwc3_host_get_irq(dwc);
	if (irq < 0)
		return irq;

	res = platform_get_resource_byname(dwc3_pdev, IORESOURCE_IRQ, "host");
	if (!res)
		res = platform_get_resource_byname(dwc3_pdev, IORESOURCE_IRQ,
				"dwc_usb3");
	if (!res)
		res = platform_get_resource(dwc3_pdev, IORESOURCE_IRQ, 0);
	if (!res)
		return -ENOMEM;

	dwc->xhci_resources[1].start = irq;
	dwc->xhci_resources[1].end = irq;
	dwc->xhci_resources[1].flags = res->flags;
	dwc->xhci_resources[1].name = res->name;

	xhci = platform_device_alloc("xhci-hcd", PLATFORM_DEVID_AUTO);
	if (!xhci) {
		dev_err(dwc->dev, "couldn't allocate xHCI device\n");
		return -ENOMEM;
	}

	xhci->dev.parent	= dwc->dev;

	dwc->xhci = xhci;

	ret = platform_device_add_resources(xhci, dwc->xhci_resources,
						DWC3_XHCI_RESOURCES_NUM);
	if (ret) {
		dev_err(dwc->dev, "couldn't add resources to xHCI device\n");
		goto err;
	}

	memset(props, 0, sizeof(struct property_entry) * ARRAY_SIZE(props));

	if (dwc->usb3_lpm_capable)
		props[prop_idx++].name = "usb3-lpm-capable";

	if (dwc->usb2_lpm_disable)
		props[prop_idx++].name = "usb2-lpm-disable";

	/**
	 * WORKAROUND: dwc3 revisions <=3.00a have a limitation
	 * where Port Disable command doesn't work.
	 *
	 * The suggested workaround is that we avoid Port Disable
	 * completely.
	 *
	 * This following flag tells XHCI to do just that.
	 */
	if (dwc->revision <= DWC3_REVISION_300A)
		props[prop_idx++].name = "quirk-broken-port-ped";

	if (prop_idx) {
		ret = platform_device_add_properties(xhci, props);
		if (ret) {
			dev_err(dwc->dev, "failed to add properties to xHCI\n");
			goto err;
		}
	}

	ret = platform_device_add(xhci);
	if (ret) {
		dev_err(dwc->dev, "failed to register xHCI device\n");
		goto err;
	}

	return 0;
err:
	platform_device_put(xhci);
	return ret;
}
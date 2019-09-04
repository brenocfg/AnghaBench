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
struct usbhs_omap_platform_data {int dummy; } ;
struct resource {int dummy; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  IORESOURCE_IRQ ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  OMAP_EHCI_DEVICE ; 
 int /*<<< orphan*/  OMAP_OHCI_DEVICE ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct usbhs_omap_platform_data* dev_get_platdata (struct device*) ; 
 struct platform_device* omap_usbhs_alloc_child (int /*<<< orphan*/ ,struct resource*,int,struct usbhs_omap_platform_data*,int,struct device*) ; 
 int /*<<< orphan*/  platform_device_unregister (struct platform_device*) ; 
 struct resource* platform_get_resource_byname (struct platform_device*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int omap_usbhs_alloc_children(struct platform_device *pdev)
{
	struct device				*dev = &pdev->dev;
	struct usbhs_omap_platform_data		*pdata = dev_get_platdata(dev);
	struct platform_device			*ehci;
	struct platform_device			*ohci;
	struct resource				*res;
	struct resource				resources[2];
	int					ret;

	res = platform_get_resource_byname(pdev, IORESOURCE_MEM, "ehci");
	if (!res) {
		dev_err(dev, "EHCI get resource IORESOURCE_MEM failed\n");
		ret = -ENODEV;
		goto err_end;
	}
	resources[0] = *res;

	res = platform_get_resource_byname(pdev, IORESOURCE_IRQ, "ehci-irq");
	if (!res) {
		dev_err(dev, " EHCI get resource IORESOURCE_IRQ failed\n");
		ret = -ENODEV;
		goto err_end;
	}
	resources[1] = *res;

	ehci = omap_usbhs_alloc_child(OMAP_EHCI_DEVICE, resources, 2, pdata,
		sizeof(*pdata), dev);

	if (!ehci) {
		dev_err(dev, "omap_usbhs_alloc_child failed\n");
		ret = -ENOMEM;
		goto err_end;
	}

	res = platform_get_resource_byname(pdev, IORESOURCE_MEM, "ohci");
	if (!res) {
		dev_err(dev, "OHCI get resource IORESOURCE_MEM failed\n");
		ret = -ENODEV;
		goto err_ehci;
	}
	resources[0] = *res;

	res = platform_get_resource_byname(pdev, IORESOURCE_IRQ, "ohci-irq");
	if (!res) {
		dev_err(dev, "OHCI get resource IORESOURCE_IRQ failed\n");
		ret = -ENODEV;
		goto err_ehci;
	}
	resources[1] = *res;

	ohci = omap_usbhs_alloc_child(OMAP_OHCI_DEVICE, resources, 2, pdata,
		sizeof(*pdata), dev);
	if (!ohci) {
		dev_err(dev, "omap_usbhs_alloc_child failed\n");
		ret = -ENOMEM;
		goto err_ehci;
	}

	return 0;

err_ehci:
	platform_device_unregister(ehci);

err_end:
	return ret;
}
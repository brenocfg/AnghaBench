#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_1__ dev; } ;
struct cdns3 {int /*<<< orphan*/  dev; int /*<<< orphan*/  xhci_res; struct platform_device* host_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CDNS3_XHCI_RESOURCES_NUM ; 
 int ENOMEM ; 
 int /*<<< orphan*/  PLATFORM_DEVID_AUTO ; 
 int /*<<< orphan*/  cdns3_drd_switch_host (struct cdns3*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int platform_device_add (struct platform_device*) ; 
 int platform_device_add_resources (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct platform_device* platform_device_alloc (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_device_put (struct platform_device*) ; 

__attribute__((used)) static int __cdns3_host_init(struct cdns3 *cdns)
{
	struct platform_device *xhci;
	int ret;

	cdns3_drd_switch_host(cdns, 1);

	xhci = platform_device_alloc("xhci-hcd", PLATFORM_DEVID_AUTO);
	if (!xhci) {
		dev_err(cdns->dev, "couldn't allocate xHCI device\n");
		return -ENOMEM;
	}

	xhci->dev.parent = cdns->dev;
	cdns->host_dev = xhci;

	ret = platform_device_add_resources(xhci, cdns->xhci_res,
					    CDNS3_XHCI_RESOURCES_NUM);
	if (ret) {
		dev_err(cdns->dev, "couldn't add resources to xHCI device\n");
		goto err1;
	}

	ret = platform_device_add(xhci);
	if (ret) {
		dev_err(cdns->dev, "failed to register xHCI device\n");
		goto err1;
	}

	return 0;
err1:
	platform_device_put(xhci);
	return ret;
}
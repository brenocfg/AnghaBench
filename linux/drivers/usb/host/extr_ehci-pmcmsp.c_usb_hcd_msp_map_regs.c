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
struct resource {int /*<<< orphan*/  start; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct mspusb_device {int /*<<< orphan*/ * mab_regs; int /*<<< orphan*/ * usbid_regs; struct platform_device dev; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 void* ioremap_nocache (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ *) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  request_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 

__attribute__((used)) static int usb_hcd_msp_map_regs(struct mspusb_device *dev)
{
	struct resource *res;
	struct platform_device *pdev = &dev->dev;
	u32 res_len;
	int retval;

	/* MAB register space */
	res = platform_get_resource(pdev, IORESOURCE_MEM, 1);
	if (res == NULL)
		return -ENOMEM;
	res_len = resource_size(res);
	if (!request_mem_region(res->start, res_len, "mab regs"))
		return -EBUSY;

	dev->mab_regs = ioremap_nocache(res->start, res_len);
	if (dev->mab_regs == NULL) {
		retval = -ENOMEM;
		goto err1;
	}

	/* MSP USB register space */
	res = platform_get_resource(pdev, IORESOURCE_MEM, 2);
	if (res == NULL) {
		retval = -ENOMEM;
		goto err2;
	}
	res_len = resource_size(res);
	if (!request_mem_region(res->start, res_len, "usbid regs")) {
		retval = -EBUSY;
		goto err2;
	}
	dev->usbid_regs = ioremap_nocache(res->start, res_len);
	if (dev->usbid_regs == NULL) {
		retval = -ENOMEM;
		goto err3;
	}

	return 0;
err3:
	res = platform_get_resource(pdev, IORESOURCE_MEM, 2);
	res_len = resource_size(res);
	release_mem_region(res->start, res_len);
err2:
	iounmap(dev->mab_regs);
err1:
	res = platform_get_resource(pdev, IORESOURCE_MEM, 1);
	res_len = resource_size(res);
	release_mem_region(res->start, res_len);
	dev_err(&pdev->dev, "Failed to map non-EHCI regs.\n");
	return retval;
}
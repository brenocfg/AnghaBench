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
struct resource {int start; } ;
struct TYPE_2__ {struct device_node* of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct orion_watchdog {void* rstout_mask; void* rstout; void* reg; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int INTERNAL_REGS_MASK ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 void* devm_ioremap (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 void* devm_platform_ioremap_resource (struct platform_device*,int) ; 
 scalar_t__ of_device_is_compatible (struct device_node*,char*) ; 
 void* orion_wdt_ioremap_rstout (struct platform_device*,int) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 

__attribute__((used)) static int orion_wdt_get_regs(struct platform_device *pdev,
			      struct orion_watchdog *dev)
{
	struct device_node *node = pdev->dev.of_node;
	struct resource *res;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!res)
		return -ENODEV;
	dev->reg = devm_ioremap(&pdev->dev, res->start,
				resource_size(res));
	if (!dev->reg)
		return -ENOMEM;

	/* Each supported compatible has some RSTOUT register quirk */
	if (of_device_is_compatible(node, "marvell,orion-wdt")) {

		dev->rstout = orion_wdt_ioremap_rstout(pdev, res->start &
						       INTERNAL_REGS_MASK);
		if (!dev->rstout)
			return -ENODEV;

	} else if (of_device_is_compatible(node, "marvell,armada-370-wdt") ||
		   of_device_is_compatible(node, "marvell,armada-xp-wdt")) {

		/* Dedicated RSTOUT register, can be requested. */
		dev->rstout = devm_platform_ioremap_resource(pdev, 1);
		if (IS_ERR(dev->rstout))
			return PTR_ERR(dev->rstout);

	} else if (of_device_is_compatible(node, "marvell,armada-375-wdt") ||
		   of_device_is_compatible(node, "marvell,armada-380-wdt")) {

		/* Dedicated RSTOUT register, can be requested. */
		dev->rstout = devm_platform_ioremap_resource(pdev, 1);
		if (IS_ERR(dev->rstout))
			return PTR_ERR(dev->rstout);

		res = platform_get_resource(pdev, IORESOURCE_MEM, 2);
		if (!res)
			return -ENODEV;
		dev->rstout_mask = devm_ioremap(&pdev->dev, res->start,
						resource_size(res));
		if (!dev->rstout_mask)
			return -ENOMEM;

	} else {
		return -ENODEV;
	}

	return 0;
}
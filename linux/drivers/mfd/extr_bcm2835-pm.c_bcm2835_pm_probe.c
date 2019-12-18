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
struct resource {int dummy; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct bcm2835_pm {void* asb; void* base; struct device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  bcm2835_pm_devs ; 
 int /*<<< orphan*/  bcm2835_power_devs ; 
 void* devm_ioremap_resource (struct device*,struct resource*) ; 
 struct bcm2835_pm* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_mfd_add_devices (struct device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct bcm2835_pm*) ; 

__attribute__((used)) static int bcm2835_pm_probe(struct platform_device *pdev)
{
	struct resource *res;
	struct device *dev = &pdev->dev;
	struct bcm2835_pm *pm;
	int ret;

	pm = devm_kzalloc(dev, sizeof(*pm), GFP_KERNEL);
	if (!pm)
		return -ENOMEM;
	platform_set_drvdata(pdev, pm);

	pm->dev = dev;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	pm->base = devm_ioremap_resource(dev, res);
	if (IS_ERR(pm->base))
		return PTR_ERR(pm->base);

	ret = devm_mfd_add_devices(dev, -1,
				   bcm2835_pm_devs, ARRAY_SIZE(bcm2835_pm_devs),
				   NULL, 0, NULL);
	if (ret)
		return ret;

	/* We'll use the presence of the AXI ASB regs in the
	 * bcm2835-pm binding as the key for whether we can reference
	 * the full PM register range and support power domains.
	 */
	res = platform_get_resource(pdev, IORESOURCE_MEM, 1);
	if (res) {
		pm->asb = devm_ioremap_resource(dev, res);
		if (IS_ERR(pm->asb))
			return PTR_ERR(pm->asb);

		ret = devm_mfd_add_devices(dev, -1,
					   bcm2835_power_devs,
					   ARRAY_SIZE(bcm2835_power_devs),
					   NULL, 0, NULL);
		if (ret)
			return ret;
	}

	return 0;
}
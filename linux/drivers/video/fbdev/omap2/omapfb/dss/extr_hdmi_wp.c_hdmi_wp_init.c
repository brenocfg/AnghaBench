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
struct resource {int /*<<< orphan*/  start; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct hdmi_wp_data {int /*<<< orphan*/  base; int /*<<< orphan*/  phys_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSSERR (char*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 struct resource* platform_get_resource_byname (struct platform_device*,int /*<<< orphan*/ ,char*) ; 

int hdmi_wp_init(struct platform_device *pdev, struct hdmi_wp_data *wp)
{
	struct resource *res;

	res = platform_get_resource_byname(pdev, IORESOURCE_MEM, "wp");
	if (!res) {
		DSSERR("can't get WP mem resource\n");
		return -EINVAL;
	}
	wp->phys_base = res->start;

	wp->base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(wp->base)) {
		DSSERR("can't ioremap HDMI WP\n");
		return PTR_ERR(wp->base);
	}

	return 0;
}
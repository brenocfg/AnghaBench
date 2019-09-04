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
struct hdmi_wp_data {unsigned int version; int /*<<< orphan*/  phys_base; int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 struct resource* platform_get_resource_byname (struct platform_device*,int /*<<< orphan*/ ,char*) ; 

int hdmi_wp_init(struct platform_device *pdev, struct hdmi_wp_data *wp,
		 unsigned int version)
{
	struct resource *res;

	res = platform_get_resource_byname(pdev, IORESOURCE_MEM, "wp");
	wp->base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(wp->base))
		return PTR_ERR(wp->base);

	wp->phys_base = res->start;
	wp->version = version;

	return 0;
}
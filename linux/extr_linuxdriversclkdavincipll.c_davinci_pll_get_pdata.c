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
struct device {scalar_t__ of_node; } ;
struct davinci_pll_platform_data {int /*<<< orphan*/  cfgchip; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct davinci_pll_platform_data* dev_get_platdata (struct device*) ; 
 struct davinci_pll_platform_data* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  syscon_regmap_lookup_by_compatible (char*) ; 

__attribute__((used)) static struct davinci_pll_platform_data *davinci_pll_get_pdata(struct device *dev)
{
	struct davinci_pll_platform_data *pdata = dev_get_platdata(dev);

	/*
	 * Platform data is optional, so allocate a new struct if one was not
	 * provided. For device tree, this will always be the case.
	 */
	if (!pdata)
		pdata = devm_kzalloc(dev, sizeof(*pdata), GFP_KERNEL);
	if (!pdata)
		return NULL;

	/* for device tree, we need to fill in the struct */
	if (dev->of_node)
		pdata->cfgchip =
			syscon_regmap_lookup_by_compatible("ti,da830-cfgchip");

	return pdata;
}
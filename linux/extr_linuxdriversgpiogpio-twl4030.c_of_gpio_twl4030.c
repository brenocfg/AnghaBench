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
struct twl4030_gpio_platform_data {int /*<<< orphan*/  pulldowns; int /*<<< orphan*/  pullups; int /*<<< orphan*/  mmc_cd; int /*<<< orphan*/  debounce; int /*<<< orphan*/  use_leds; } ;
struct device {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct twl4030_gpio_platform_data* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_property_read_bool (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  of_property_read_u32 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct twl4030_gpio_platform_data *of_gpio_twl4030(struct device *dev,
				struct twl4030_gpio_platform_data *pdata)
{
	struct twl4030_gpio_platform_data *omap_twl_info;

	omap_twl_info = devm_kzalloc(dev, sizeof(*omap_twl_info), GFP_KERNEL);
	if (!omap_twl_info)
		return NULL;

	if (pdata)
		*omap_twl_info = *pdata;

	omap_twl_info->use_leds = of_property_read_bool(dev->of_node,
			"ti,use-leds");

	of_property_read_u32(dev->of_node, "ti,debounce",
			     &omap_twl_info->debounce);
	of_property_read_u32(dev->of_node, "ti,mmc-cd",
			     (u32 *)&omap_twl_info->mmc_cd);
	of_property_read_u32(dev->of_node, "ti,pullups",
			     &omap_twl_info->pullups);
	of_property_read_u32(dev->of_node, "ti,pulldowns",
			     &omap_twl_info->pulldowns);

	return omap_twl_info;
}
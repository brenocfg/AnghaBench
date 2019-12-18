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
typedef  scalar_t__ uint32_t ;
struct stfsm {int booted_from_spi; void* reset_por; void* reset_signal; } ;
struct regmap {int dummy; } ;
struct TYPE_2__ {struct device_node* of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct regmap*) ; 
 int /*<<< orphan*/  dev_warn (TYPE_1__*,char*) ; 
 void* of_property_read_bool (struct device_node*,char*) ; 
 int of_property_read_u32 (struct device_node*,char*,scalar_t__*) ; 
 struct stfsm* platform_get_drvdata (struct platform_device*) ; 
 int regmap_read (struct regmap*,scalar_t__,scalar_t__*) ; 
 struct regmap* syscon_regmap_lookup_by_phandle (struct device_node*,char*) ; 

__attribute__((used)) static void stfsm_fetch_platform_configs(struct platform_device *pdev)
{
	struct stfsm *fsm = platform_get_drvdata(pdev);
	struct device_node *np = pdev->dev.of_node;
	struct regmap *regmap;
	uint32_t boot_device_reg;
	uint32_t boot_device_spi;
	uint32_t boot_device;     /* Value we read from *boot_device_reg */
	int ret;

	/* Booting from SPI NOR Flash is the default */
	fsm->booted_from_spi = true;

	regmap = syscon_regmap_lookup_by_phandle(np, "st,syscfg");
	if (IS_ERR(regmap))
		goto boot_device_fail;

	fsm->reset_signal = of_property_read_bool(np, "st,reset-signal");

	fsm->reset_por = of_property_read_bool(np, "st,reset-por");

	/* Where in the syscon the boot device information lives */
	ret = of_property_read_u32(np, "st,boot-device-reg", &boot_device_reg);
	if (ret)
		goto boot_device_fail;

	/* Boot device value when booted from SPI NOR */
	ret = of_property_read_u32(np, "st,boot-device-spi", &boot_device_spi);
	if (ret)
		goto boot_device_fail;

	ret = regmap_read(regmap, boot_device_reg, &boot_device);
	if (ret)
		goto boot_device_fail;

	if (boot_device != boot_device_spi)
		fsm->booted_from_spi = false;

	return;

boot_device_fail:
	dev_warn(&pdev->dev,
		 "failed to fetch boot device, assuming boot from SPI\n");
}
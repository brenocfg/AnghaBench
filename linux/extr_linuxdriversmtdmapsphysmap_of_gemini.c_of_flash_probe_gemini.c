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
typedef  int u32 ;
struct regmap {int dummy; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct map_info {int bankwidth; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int FLASH_TYPE_MASK ; 
 int FLASH_TYPE_PARALLEL ; 
 int FLASH_WIDTH_16BIT ; 
 int /*<<< orphan*/  GLOBAL_STATUS ; 
 scalar_t__ IS_ERR (struct regmap*) ; 
 int PTR_ERR (struct regmap*) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,int) ; 
 int /*<<< orphan*/  of_device_is_compatible (struct device_node*,char*) ; 
 int regmap_read (struct regmap*,int /*<<< orphan*/ ,int*) ; 
 struct regmap* syscon_regmap_lookup_by_phandle (struct device_node*,char*) ; 

int of_flash_probe_gemini(struct platform_device *pdev,
			  struct device_node *np,
			  struct map_info *map)
{
	struct regmap *rmap;
	struct device *dev = &pdev->dev;
	u32 val;
	int ret;

	/* Multiplatform guard */
	if (!of_device_is_compatible(np, "cortina,gemini-flash"))
		return 0;

	rmap = syscon_regmap_lookup_by_phandle(np, "syscon");
	if (IS_ERR(rmap)) {
		dev_err(dev, "no syscon\n");
		return PTR_ERR(rmap);
	}

	ret = regmap_read(rmap, GLOBAL_STATUS, &val);
	if (ret) {
		dev_err(dev, "failed to read global status register\n");
		return -ENODEV;
	}
	dev_dbg(dev, "global status reg: %08x\n", val);

	/*
	 * It would be contradictory if a physmap flash was NOT parallel.
	 */
	if ((val & FLASH_TYPE_MASK) != FLASH_TYPE_PARALLEL) {
		dev_err(dev, "flash is not parallel\n");
		return -ENODEV;
	}

	/*
	 * Complain if DT data and hardware definition is different.
	 */
	if (val & FLASH_WIDTH_16BIT) {
		if (map->bankwidth != 2)
			dev_warn(dev, "flash hardware say flash is 16 bit wide but DT says it is %d bits wide\n",
				 map->bankwidth * 8);
	} else {
		if (map->bankwidth != 1)
			dev_warn(dev, "flash hardware say flash is 8 bit wide but DT says it is %d bits wide\n",
				 map->bankwidth * 8);
	}

	dev_info(&pdev->dev, "initialized Gemini-specific physmap control\n");

	return 0;
}
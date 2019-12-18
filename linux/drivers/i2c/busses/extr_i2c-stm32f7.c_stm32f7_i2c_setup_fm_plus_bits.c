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
typedef  int /*<<< orphan*/  u32 ;
struct stm32f7_i2c_dev {int /*<<< orphan*/  regmap; } ;
struct TYPE_2__ {struct device_node* of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int of_property_read_u32_index (struct device_node*,char*,int,int /*<<< orphan*/ *) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  syscon_regmap_lookup_by_phandle (struct device_node*,char*) ; 

__attribute__((used)) static int stm32f7_i2c_setup_fm_plus_bits(struct platform_device *pdev,
					  struct stm32f7_i2c_dev *i2c_dev)
{
	struct device_node *np = pdev->dev.of_node;
	int ret;
	u32 reg, mask;

	i2c_dev->regmap = syscon_regmap_lookup_by_phandle(np, "st,syscfg-fmp");
	if (IS_ERR(i2c_dev->regmap)) {
		/* Optional */
		return 0;
	}

	ret = of_property_read_u32_index(np, "st,syscfg-fmp", 1, &reg);
	if (ret)
		return ret;

	ret = of_property_read_u32_index(np, "st,syscfg-fmp", 2, &mask);
	if (ret)
		return ret;

	return regmap_update_bits(i2c_dev->regmap, reg, mask, mask);
}
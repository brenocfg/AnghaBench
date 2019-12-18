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
struct regmap {int dummy; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct regmap*) ; 
 int PTR_ERR (struct regmap*) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct regmap*) ; 
 struct regmap* devm_regmap_init_vexpress_config (struct device*) ; 

__attribute__((used)) static int vexpress_muxfpga_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct regmap *map;

	map = devm_regmap_init_vexpress_config(&pdev->dev);
	if (IS_ERR(map))
		return PTR_ERR(map);
	dev_set_drvdata(dev, map);

	return 0;
}
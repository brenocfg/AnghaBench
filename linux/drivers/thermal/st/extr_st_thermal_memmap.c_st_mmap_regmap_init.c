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
struct st_thermal_sensor {int /*<<< orphan*/  regmap; int /*<<< orphan*/  mmio_base; struct device* dev; } ;
struct resource {int dummy; } ;
struct platform_device {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (struct device*,struct resource*) ; 
 int /*<<< orphan*/  devm_regmap_init_mmio (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  st_416mpe_regmap_config ; 
 struct platform_device* to_platform_device (struct device*) ; 

__attribute__((used)) static int st_mmap_regmap_init(struct st_thermal_sensor *sensor)
{
	struct device *dev = sensor->dev;
	struct platform_device *pdev = to_platform_device(dev);
	struct resource *res;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!res) {
		dev_err(dev, "no memory resources defined\n");
		return -ENODEV;
	}

	sensor->mmio_base = devm_ioremap_resource(dev, res);
	if (IS_ERR(sensor->mmio_base)) {
		dev_err(dev, "failed to remap IO\n");
		return PTR_ERR(sensor->mmio_base);
	}

	sensor->regmap = devm_regmap_init_mmio(dev, sensor->mmio_base,
				&st_416mpe_regmap_config);
	if (IS_ERR(sensor->regmap)) {
		dev_err(dev, "failed to initialise regmap\n");
		return PTR_ERR(sensor->regmap);
	}

	return 0;
}
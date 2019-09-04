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
struct atmel_hlcdc_regmap {void* regs; } ;
struct atmel_hlcdc {scalar_t__ irq; void* regmap; void* slow_clk; void* sys_clk; void* periph_clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  atmel_hlcdc_cells ; 
 int /*<<< orphan*/  atmel_hlcdc_regmap_config ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct atmel_hlcdc*) ; 
 void* devm_clk_get (struct device*,char*) ; 
 void* devm_ioremap_resource (struct device*,struct resource*) ; 
 void* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_mfd_add_devices (struct device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* devm_regmap_init (struct device*,int /*<<< orphan*/ *,struct atmel_hlcdc_regmap*,int /*<<< orphan*/ *) ; 
 scalar_t__ platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int atmel_hlcdc_probe(struct platform_device *pdev)
{
	struct atmel_hlcdc_regmap *hregmap;
	struct device *dev = &pdev->dev;
	struct atmel_hlcdc *hlcdc;
	struct resource *res;

	hregmap = devm_kzalloc(dev, sizeof(*hregmap), GFP_KERNEL);
	if (!hregmap)
		return -ENOMEM;

	hlcdc = devm_kzalloc(dev, sizeof(*hlcdc), GFP_KERNEL);
	if (!hlcdc)
		return -ENOMEM;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	hregmap->regs = devm_ioremap_resource(dev, res);
	if (IS_ERR(hregmap->regs))
		return PTR_ERR(hregmap->regs);

	hlcdc->irq = platform_get_irq(pdev, 0);
	if (hlcdc->irq < 0)
		return hlcdc->irq;

	hlcdc->periph_clk = devm_clk_get(dev, "periph_clk");
	if (IS_ERR(hlcdc->periph_clk)) {
		dev_err(dev, "failed to get peripheral clock\n");
		return PTR_ERR(hlcdc->periph_clk);
	}

	hlcdc->sys_clk = devm_clk_get(dev, "sys_clk");
	if (IS_ERR(hlcdc->sys_clk)) {
		dev_err(dev, "failed to get system clock\n");
		return PTR_ERR(hlcdc->sys_clk);
	}

	hlcdc->slow_clk = devm_clk_get(dev, "slow_clk");
	if (IS_ERR(hlcdc->slow_clk)) {
		dev_err(dev, "failed to get slow clock\n");
		return PTR_ERR(hlcdc->slow_clk);
	}

	hlcdc->regmap = devm_regmap_init(dev, NULL, hregmap,
					 &atmel_hlcdc_regmap_config);
	if (IS_ERR(hlcdc->regmap))
		return PTR_ERR(hlcdc->regmap);

	dev_set_drvdata(dev, hlcdc);

	return devm_mfd_add_devices(dev, -1, atmel_hlcdc_cells,
				    ARRAY_SIZE(atmel_hlcdc_cells),
				    NULL, 0, NULL);
}
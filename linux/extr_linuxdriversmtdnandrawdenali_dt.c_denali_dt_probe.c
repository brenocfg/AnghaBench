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
struct denali_nand_info {scalar_t__ irq; int clk_rate; int clk_x_rate; int /*<<< orphan*/ * host; int /*<<< orphan*/ * reg; struct device* dev; int /*<<< orphan*/  ecc_caps; int /*<<< orphan*/  caps; int /*<<< orphan*/  revision; } ;
struct denali_dt_data {int /*<<< orphan*/  ecc_caps; int /*<<< orphan*/  caps; int /*<<< orphan*/  revision; } ;
struct denali_dt {int /*<<< orphan*/ * clk; int /*<<< orphan*/ * clk_x; int /*<<< orphan*/ * clk_ecc; struct denali_nand_info denali; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ *) ; 
 void* clk_get_rate (int /*<<< orphan*/ *) ; 
 int clk_prepare_enable (int /*<<< orphan*/ *) ; 
 int denali_init (struct denali_nand_info*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_notice (struct device*,char*) ; 
 void* devm_clk_get (struct device*,char*) ; 
 void* devm_ioremap_resource (struct device*,struct resource*) ; 
 struct denali_dt* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 struct denali_dt_data* of_device_get_match_data (struct device*) ; 
 scalar_t__ platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource_byname (struct platform_device*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct denali_dt*) ; 

__attribute__((used)) static int denali_dt_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct resource *res;
	struct denali_dt *dt;
	const struct denali_dt_data *data;
	struct denali_nand_info *denali;
	int ret;

	dt = devm_kzalloc(dev, sizeof(*dt), GFP_KERNEL);
	if (!dt)
		return -ENOMEM;
	denali = &dt->denali;

	data = of_device_get_match_data(dev);
	if (data) {
		denali->revision = data->revision;
		denali->caps = data->caps;
		denali->ecc_caps = data->ecc_caps;
	}

	denali->dev = dev;
	denali->irq = platform_get_irq(pdev, 0);
	if (denali->irq < 0) {
		dev_err(dev, "no irq defined\n");
		return denali->irq;
	}

	res = platform_get_resource_byname(pdev, IORESOURCE_MEM, "denali_reg");
	denali->reg = devm_ioremap_resource(dev, res);
	if (IS_ERR(denali->reg))
		return PTR_ERR(denali->reg);

	res = platform_get_resource_byname(pdev, IORESOURCE_MEM, "nand_data");
	denali->host = devm_ioremap_resource(dev, res);
	if (IS_ERR(denali->host))
		return PTR_ERR(denali->host);

	/*
	 * A single anonymous clock is supported for the backward compatibility.
	 * New platforms should support all the named clocks.
	 */
	dt->clk = devm_clk_get(dev, "nand");
	if (IS_ERR(dt->clk))
		dt->clk = devm_clk_get(dev, NULL);
	if (IS_ERR(dt->clk)) {
		dev_err(dev, "no clk available\n");
		return PTR_ERR(dt->clk);
	}

	dt->clk_x = devm_clk_get(dev, "nand_x");
	if (IS_ERR(dt->clk_x))
		dt->clk_x = NULL;

	dt->clk_ecc = devm_clk_get(dev, "ecc");
	if (IS_ERR(dt->clk_ecc))
		dt->clk_ecc = NULL;

	ret = clk_prepare_enable(dt->clk);
	if (ret)
		return ret;

	ret = clk_prepare_enable(dt->clk_x);
	if (ret)
		goto out_disable_clk;

	ret = clk_prepare_enable(dt->clk_ecc);
	if (ret)
		goto out_disable_clk_x;

	if (dt->clk_x) {
		denali->clk_rate = clk_get_rate(dt->clk);
		denali->clk_x_rate = clk_get_rate(dt->clk_x);
	} else {
		/*
		 * Hardcode the clock rates for the backward compatibility.
		 * This works for both SOCFPGA and UniPhier.
		 */
		dev_notice(dev,
			   "necessary clock is missing. default clock rates are used.\n");
		denali->clk_rate = 50000000;
		denali->clk_x_rate = 200000000;
	}

	ret = denali_init(denali);
	if (ret)
		goto out_disable_clk_ecc;

	platform_set_drvdata(pdev, dt);
	return 0;

out_disable_clk_ecc:
	clk_disable_unprepare(dt->clk_ecc);
out_disable_clk_x:
	clk_disable_unprepare(dt->clk_x);
out_disable_clk:
	clk_disable_unprepare(dt->clk);

	return ret;
}
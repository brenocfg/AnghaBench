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
struct tegra_gmi {int /*<<< orphan*/  rst; int /*<<< orphan*/  clk; int /*<<< orphan*/  base; struct device* dev; } ;
struct resource {int dummy; } ;
struct device {int /*<<< orphan*/  of_node; } ;
struct platform_device {struct device dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  devm_clk_get (struct device*,char*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (struct device*,struct resource*) ; 
 struct tegra_gmi* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_reset_control_get (struct device*,char*) ; 
 int of_platform_default_populate (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct device*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct tegra_gmi*) ; 
 int /*<<< orphan*/  tegra_gmi_disable (struct tegra_gmi*) ; 
 int tegra_gmi_enable (struct tegra_gmi*) ; 
 int tegra_gmi_parse_dt (struct tegra_gmi*) ; 

__attribute__((used)) static int tegra_gmi_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct tegra_gmi *gmi;
	struct resource *res;
	int err;

	gmi = devm_kzalloc(dev, sizeof(*gmi), GFP_KERNEL);
	if (!gmi)
		return -ENOMEM;

	gmi->dev = dev;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	gmi->base = devm_ioremap_resource(dev, res);
	if (IS_ERR(gmi->base))
		return PTR_ERR(gmi->base);

	gmi->clk = devm_clk_get(dev, "gmi");
	if (IS_ERR(gmi->clk)) {
		dev_err(dev, "can not get clock\n");
		return PTR_ERR(gmi->clk);
	}

	gmi->rst = devm_reset_control_get(dev, "gmi");
	if (IS_ERR(gmi->rst)) {
		dev_err(dev, "can not get reset\n");
		return PTR_ERR(gmi->rst);
	}

	err = tegra_gmi_parse_dt(gmi);
	if (err)
		return err;

	err = tegra_gmi_enable(gmi);
	if (err < 0)
		return err;

	err = of_platform_default_populate(dev->of_node, NULL, dev);
	if (err < 0) {
		dev_err(dev, "fail to create devices.\n");
		tegra_gmi_disable(gmi);
		return err;
	}

	platform_set_drvdata(pdev, gmi);

	return 0;
}
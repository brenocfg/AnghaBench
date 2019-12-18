#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct resource {int dummy; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct TYPE_5__ {struct device* dev; int /*<<< orphan*/ * ops; } ;
struct exynos_dsi {scalar_t__ irq; int /*<<< orphan*/  encoder; int /*<<< orphan*/  phy; int /*<<< orphan*/  reg_base; int /*<<< orphan*/ * clks; TYPE_2__* driver_data; TYPE_3__* supplies; struct device* dev; TYPE_1__ dsi_host; int /*<<< orphan*/  transfer_list; int /*<<< orphan*/  transfer_lock; int /*<<< orphan*/  completed; int /*<<< orphan*/  te_gpio; } ;
struct TYPE_7__ {char* supply; } ;
struct TYPE_6__ {int num_clks; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (TYPE_3__*) ; 
 int /*<<< orphan*/  ENOENT ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  IRQF_ONESHOT ; 
 int /*<<< orphan*/  IRQ_NOAUTOEN ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OLD_SCLK_MIPI_CLK_NAME ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * clk_names ; 
 int component_add (struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int /*<<< orphan*/  devm_clk_get (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_ioremap_resource (struct device*,struct resource*) ; 
 int /*<<< orphan*/ * devm_kcalloc (struct device*,int,int,int /*<<< orphan*/ ) ; 
 struct exynos_dsi* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_phy_get (struct device*,char*) ; 
 int devm_regulator_bulk_get (struct device*,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int devm_request_threaded_irq (struct device*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct exynos_dsi*) ; 
 int /*<<< orphan*/  exynos_dsi_component_ops ; 
 int /*<<< orphan*/  exynos_dsi_irq ; 
 int /*<<< orphan*/  exynos_dsi_ops ; 
 int exynos_dsi_parse_dt (struct exynos_dsi*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  irq_set_status_flags (int,int /*<<< orphan*/ ) ; 
 TYPE_2__* of_device_get_match_data (struct device*) ; 
 scalar_t__ platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_enable (struct device*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int exynos_dsi_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct resource *res;
	struct exynos_dsi *dsi;
	int ret, i;

	dsi = devm_kzalloc(dev, sizeof(*dsi), GFP_KERNEL);
	if (!dsi)
		return -ENOMEM;

	/* To be checked as invalid one */
	dsi->te_gpio = -ENOENT;

	init_completion(&dsi->completed);
	spin_lock_init(&dsi->transfer_lock);
	INIT_LIST_HEAD(&dsi->transfer_list);

	dsi->dsi_host.ops = &exynos_dsi_ops;
	dsi->dsi_host.dev = dev;

	dsi->dev = dev;
	dsi->driver_data = of_device_get_match_data(dev);

	ret = exynos_dsi_parse_dt(dsi);
	if (ret)
		return ret;

	dsi->supplies[0].supply = "vddcore";
	dsi->supplies[1].supply = "vddio";
	ret = devm_regulator_bulk_get(dev, ARRAY_SIZE(dsi->supplies),
				      dsi->supplies);
	if (ret) {
		dev_info(dev, "failed to get regulators: %d\n", ret);
		return -EPROBE_DEFER;
	}

	dsi->clks = devm_kcalloc(dev,
			dsi->driver_data->num_clks, sizeof(*dsi->clks),
			GFP_KERNEL);
	if (!dsi->clks)
		return -ENOMEM;

	for (i = 0; i < dsi->driver_data->num_clks; i++) {
		dsi->clks[i] = devm_clk_get(dev, clk_names[i]);
		if (IS_ERR(dsi->clks[i])) {
			if (strcmp(clk_names[i], "sclk_mipi") == 0) {
				strcpy(clk_names[i], OLD_SCLK_MIPI_CLK_NAME);
				i--;
				continue;
			}

			dev_info(dev, "failed to get the clock: %s\n",
					clk_names[i]);
			return PTR_ERR(dsi->clks[i]);
		}
	}

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	dsi->reg_base = devm_ioremap_resource(dev, res);
	if (IS_ERR(dsi->reg_base)) {
		dev_err(dev, "failed to remap io region\n");
		return PTR_ERR(dsi->reg_base);
	}

	dsi->phy = devm_phy_get(dev, "dsim");
	if (IS_ERR(dsi->phy)) {
		dev_info(dev, "failed to get dsim phy\n");
		return PTR_ERR(dsi->phy);
	}

	dsi->irq = platform_get_irq(pdev, 0);
	if (dsi->irq < 0) {
		dev_err(dev, "failed to request dsi irq resource\n");
		return dsi->irq;
	}

	irq_set_status_flags(dsi->irq, IRQ_NOAUTOEN);
	ret = devm_request_threaded_irq(dev, dsi->irq, NULL,
					exynos_dsi_irq, IRQF_ONESHOT,
					dev_name(dev), dsi);
	if (ret) {
		dev_err(dev, "failed to request dsi irq\n");
		return ret;
	}

	platform_set_drvdata(pdev, &dsi->encoder);

	pm_runtime_enable(dev);

	return component_add(dev, &exynos_dsi_component_ops);
}
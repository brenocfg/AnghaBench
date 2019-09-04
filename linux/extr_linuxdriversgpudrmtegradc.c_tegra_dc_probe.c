#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * dev; int /*<<< orphan*/ * ops; int /*<<< orphan*/  list; } ;
struct tegra_dc {scalar_t__ pipe; scalar_t__ irq; TYPE_2__ client; int /*<<< orphan*/  regs; int /*<<< orphan*/  powergate; TYPE_1__* soc; int /*<<< orphan*/  clk; int /*<<< orphan*/  rst; int /*<<< orphan*/ * dev; int /*<<< orphan*/  list; } ;
struct resource {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {scalar_t__ has_powergate; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEGRA_POWERGATE_DIS ; 
 int /*<<< orphan*/  TEGRA_POWERGATE_DISB ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dc_client_ops ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  devm_clk_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 struct tegra_dc* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_reset_control_get (int /*<<< orphan*/ *,char*) ; 
 int host1x_client_register (TYPE_2__*) ; 
 TYPE_1__* of_device_get_match_data (int /*<<< orphan*/ *) ; 
 scalar_t__ platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct tegra_dc*) ; 
 int /*<<< orphan*/  pm_runtime_enable (int /*<<< orphan*/ *) ; 
 int reset_control_assert (int /*<<< orphan*/ ) ; 
 int tegra_dc_couple (struct tegra_dc*) ; 
 int tegra_dc_parse_dt (struct tegra_dc*) ; 
 int tegra_dc_rgb_probe (struct tegra_dc*) ; 
 int /*<<< orphan*/  tegra_powergate_power_off (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int tegra_dc_probe(struct platform_device *pdev)
{
	struct resource *regs;
	struct tegra_dc *dc;
	int err;

	dc = devm_kzalloc(&pdev->dev, sizeof(*dc), GFP_KERNEL);
	if (!dc)
		return -ENOMEM;

	dc->soc = of_device_get_match_data(&pdev->dev);

	INIT_LIST_HEAD(&dc->list);
	dc->dev = &pdev->dev;

	err = tegra_dc_parse_dt(dc);
	if (err < 0)
		return err;

	err = tegra_dc_couple(dc);
	if (err < 0)
		return err;

	dc->clk = devm_clk_get(&pdev->dev, NULL);
	if (IS_ERR(dc->clk)) {
		dev_err(&pdev->dev, "failed to get clock\n");
		return PTR_ERR(dc->clk);
	}

	dc->rst = devm_reset_control_get(&pdev->dev, "dc");
	if (IS_ERR(dc->rst)) {
		dev_err(&pdev->dev, "failed to get reset\n");
		return PTR_ERR(dc->rst);
	}

	/* assert reset and disable clock */
	err = clk_prepare_enable(dc->clk);
	if (err < 0)
		return err;

	usleep_range(2000, 4000);

	err = reset_control_assert(dc->rst);
	if (err < 0)
		return err;

	usleep_range(2000, 4000);

	clk_disable_unprepare(dc->clk);

	if (dc->soc->has_powergate) {
		if (dc->pipe == 0)
			dc->powergate = TEGRA_POWERGATE_DIS;
		else
			dc->powergate = TEGRA_POWERGATE_DISB;

		tegra_powergate_power_off(dc->powergate);
	}

	regs = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	dc->regs = devm_ioremap_resource(&pdev->dev, regs);
	if (IS_ERR(dc->regs))
		return PTR_ERR(dc->regs);

	dc->irq = platform_get_irq(pdev, 0);
	if (dc->irq < 0) {
		dev_err(&pdev->dev, "failed to get IRQ\n");
		return -ENXIO;
	}

	err = tegra_dc_rgb_probe(dc);
	if (err < 0 && err != -ENODEV) {
		dev_err(&pdev->dev, "failed to probe RGB output: %d\n", err);
		return err;
	}

	platform_set_drvdata(pdev, dc);
	pm_runtime_enable(&pdev->dev);

	INIT_LIST_HEAD(&dc->client.list);
	dc->client.ops = &dc_client_ops;
	dc->client.dev = &pdev->dev;

	err = host1x_client_register(&dc->client);
	if (err < 0) {
		dev_err(&pdev->dev, "failed to register host1x client: %d\n",
			err);
		return err;
	}

	return 0;
}
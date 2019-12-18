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
struct TYPE_3__ {int /*<<< orphan*/ * dev; } ;
struct tegra_hdmi {int stereo; int dvi; int irq; TYPE_2__ client; int /*<<< orphan*/ * dev; void* regs; TYPE_1__ output; void* vdd; void* pll; void* hdmi; void* clk_parent; void* clk; void* rst; int /*<<< orphan*/  audio_source; int /*<<< orphan*/  config; } ;
struct resource {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUTO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int clk_set_parent (void*,void*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 void* devm_clk_get (int /*<<< orphan*/ *,char*) ; 
 void* devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 struct tegra_hdmi* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 void* devm_regulator_get (int /*<<< orphan*/ *,char*) ; 
 int devm_request_irq (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct tegra_hdmi*) ; 
 void* devm_reset_control_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  hdmi_client_ops ; 
 int host1x_client_register (TYPE_2__*) ; 
 int /*<<< orphan*/  of_device_get_match_data (int /*<<< orphan*/ *) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct tegra_hdmi*) ; 
 int /*<<< orphan*/  pm_runtime_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tegra_hdmi_irq ; 
 int tegra_output_probe (TYPE_1__*) ; 

__attribute__((used)) static int tegra_hdmi_probe(struct platform_device *pdev)
{
	struct tegra_hdmi *hdmi;
	struct resource *regs;
	int err;

	hdmi = devm_kzalloc(&pdev->dev, sizeof(*hdmi), GFP_KERNEL);
	if (!hdmi)
		return -ENOMEM;

	hdmi->config = of_device_get_match_data(&pdev->dev);
	hdmi->dev = &pdev->dev;

	hdmi->audio_source = AUTO;
	hdmi->stereo = false;
	hdmi->dvi = false;

	hdmi->clk = devm_clk_get(&pdev->dev, NULL);
	if (IS_ERR(hdmi->clk)) {
		dev_err(&pdev->dev, "failed to get clock\n");
		return PTR_ERR(hdmi->clk);
	}

	hdmi->rst = devm_reset_control_get(&pdev->dev, "hdmi");
	if (IS_ERR(hdmi->rst)) {
		dev_err(&pdev->dev, "failed to get reset\n");
		return PTR_ERR(hdmi->rst);
	}

	hdmi->clk_parent = devm_clk_get(&pdev->dev, "parent");
	if (IS_ERR(hdmi->clk_parent))
		return PTR_ERR(hdmi->clk_parent);

	err = clk_set_parent(hdmi->clk, hdmi->clk_parent);
	if (err < 0) {
		dev_err(&pdev->dev, "failed to setup clocks: %d\n", err);
		return err;
	}

	hdmi->hdmi = devm_regulator_get(&pdev->dev, "hdmi");
	if (IS_ERR(hdmi->hdmi)) {
		dev_err(&pdev->dev, "failed to get HDMI regulator\n");
		return PTR_ERR(hdmi->hdmi);
	}

	hdmi->pll = devm_regulator_get(&pdev->dev, "pll");
	if (IS_ERR(hdmi->pll)) {
		dev_err(&pdev->dev, "failed to get PLL regulator\n");
		return PTR_ERR(hdmi->pll);
	}

	hdmi->vdd = devm_regulator_get(&pdev->dev, "vdd");
	if (IS_ERR(hdmi->vdd)) {
		dev_err(&pdev->dev, "failed to get VDD regulator\n");
		return PTR_ERR(hdmi->vdd);
	}

	hdmi->output.dev = &pdev->dev;

	err = tegra_output_probe(&hdmi->output);
	if (err < 0)
		return err;

	regs = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	hdmi->regs = devm_ioremap_resource(&pdev->dev, regs);
	if (IS_ERR(hdmi->regs))
		return PTR_ERR(hdmi->regs);

	err = platform_get_irq(pdev, 0);
	if (err < 0)
		return err;

	hdmi->irq = err;

	err = devm_request_irq(hdmi->dev, hdmi->irq, tegra_hdmi_irq, 0,
			       dev_name(hdmi->dev), hdmi);
	if (err < 0) {
		dev_err(&pdev->dev, "failed to request IRQ#%u: %d\n",
			hdmi->irq, err);
		return err;
	}

	platform_set_drvdata(pdev, hdmi);
	pm_runtime_enable(&pdev->dev);

	INIT_LIST_HEAD(&hdmi->client.list);
	hdmi->client.ops = &hdmi_client_ops;
	hdmi->client.dev = &pdev->dev;

	err = host1x_client_register(&hdmi->client);
	if (err < 0) {
		dev_err(&pdev->dev, "failed to register host1x client: %d\n",
			err);
		return err;
	}

	return 0;
}
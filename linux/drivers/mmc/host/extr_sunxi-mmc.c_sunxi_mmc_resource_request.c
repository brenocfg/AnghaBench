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
struct sunxi_mmc_host {scalar_t__ irq; void* reset; void* clk_sample; void* clk_output; TYPE_1__* cfg; void* clk_mmc; void* clk_ahb; void* reg_base; int /*<<< orphan*/  mmc; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {scalar_t__ clk_delays; } ;

/* Variables and functions */
 int EINVAL ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 void* devm_clk_get (int /*<<< orphan*/ *,char*) ; 
 void* devm_ioremap_resource (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int devm_request_threaded_irq (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct sunxi_mmc_host*) ; 
 void* devm_reset_control_get_optional_exclusive (int /*<<< orphan*/ *,char*) ; 
 int mmc_regulator_get_supply (int /*<<< orphan*/ ) ; 
 TYPE_1__* of_device_get_match_data (int /*<<< orphan*/ *) ; 
 scalar_t__ platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sunxi_mmc_disable (struct sunxi_mmc_host*) ; 
 int sunxi_mmc_enable (struct sunxi_mmc_host*) ; 
 int /*<<< orphan*/  sunxi_mmc_handle_manual_stop ; 
 int /*<<< orphan*/  sunxi_mmc_irq ; 

__attribute__((used)) static int sunxi_mmc_resource_request(struct sunxi_mmc_host *host,
				      struct platform_device *pdev)
{
	int ret;

	host->cfg = of_device_get_match_data(&pdev->dev);
	if (!host->cfg)
		return -EINVAL;

	ret = mmc_regulator_get_supply(host->mmc);
	if (ret)
		return ret;

	host->reg_base = devm_ioremap_resource(&pdev->dev,
			      platform_get_resource(pdev, IORESOURCE_MEM, 0));
	if (IS_ERR(host->reg_base))
		return PTR_ERR(host->reg_base);

	host->clk_ahb = devm_clk_get(&pdev->dev, "ahb");
	if (IS_ERR(host->clk_ahb)) {
		dev_err(&pdev->dev, "Could not get ahb clock\n");
		return PTR_ERR(host->clk_ahb);
	}

	host->clk_mmc = devm_clk_get(&pdev->dev, "mmc");
	if (IS_ERR(host->clk_mmc)) {
		dev_err(&pdev->dev, "Could not get mmc clock\n");
		return PTR_ERR(host->clk_mmc);
	}

	if (host->cfg->clk_delays) {
		host->clk_output = devm_clk_get(&pdev->dev, "output");
		if (IS_ERR(host->clk_output)) {
			dev_err(&pdev->dev, "Could not get output clock\n");
			return PTR_ERR(host->clk_output);
		}

		host->clk_sample = devm_clk_get(&pdev->dev, "sample");
		if (IS_ERR(host->clk_sample)) {
			dev_err(&pdev->dev, "Could not get sample clock\n");
			return PTR_ERR(host->clk_sample);
		}
	}

	host->reset = devm_reset_control_get_optional_exclusive(&pdev->dev,
								"ahb");
	if (PTR_ERR(host->reset) == -EPROBE_DEFER)
		return PTR_ERR(host->reset);

	ret = sunxi_mmc_enable(host);
	if (ret)
		return ret;

	host->irq = platform_get_irq(pdev, 0);
	if (host->irq <= 0) {
		ret = -EINVAL;
		goto error_disable_mmc;
	}

	return devm_request_threaded_irq(&pdev->dev, host->irq, sunxi_mmc_irq,
			sunxi_mmc_handle_manual_stop, 0, "sunxi-mmc", host);

error_disable_mmc:
	sunxi_mmc_disable(host);
	return ret;
}
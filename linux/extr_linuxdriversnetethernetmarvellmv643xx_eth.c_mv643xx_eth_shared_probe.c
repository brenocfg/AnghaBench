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
struct resource {int /*<<< orphan*/  start; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct mv643xx_eth_shared_private {int tx_csum_limit; int /*<<< orphan*/  clk; int /*<<< orphan*/ * base; } ;
struct mv643xx_eth_shared_platform_data {int tx_csum_limit; } ;
struct mbus_dram_target_info {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_prepare_enable (int /*<<< orphan*/ ) ; 
 struct mv643xx_eth_shared_platform_data* dev_get_platdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_clk_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * devm_ioremap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mv643xx_eth_shared_private* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  infer_hw_params (struct mv643xx_eth_shared_private*) ; 
 int /*<<< orphan*/  mv643xx_eth_conf_mbus_windows (struct mv643xx_eth_shared_private*,struct mbus_dram_target_info const*) ; 
 int /*<<< orphan*/  mv643xx_eth_driver_version ; 
 int mv643xx_eth_shared_of_probe (struct platform_device*) ; 
 struct mbus_dram_target_info* mv_mbus_dram_info () ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct mv643xx_eth_shared_private*) ; 
 int /*<<< orphan*/  pr_notice (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 

__attribute__((used)) static int mv643xx_eth_shared_probe(struct platform_device *pdev)
{
	static int mv643xx_eth_version_printed;
	struct mv643xx_eth_shared_platform_data *pd;
	struct mv643xx_eth_shared_private *msp;
	const struct mbus_dram_target_info *dram;
	struct resource *res;
	int ret;

	if (!mv643xx_eth_version_printed++)
		pr_notice("MV-643xx 10/100/1000 ethernet driver version %s\n",
			  mv643xx_eth_driver_version);

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (res == NULL)
		return -EINVAL;

	msp = devm_kzalloc(&pdev->dev, sizeof(*msp), GFP_KERNEL);
	if (msp == NULL)
		return -ENOMEM;
	platform_set_drvdata(pdev, msp);

	msp->base = devm_ioremap(&pdev->dev, res->start, resource_size(res));
	if (msp->base == NULL)
		return -ENOMEM;

	msp->clk = devm_clk_get(&pdev->dev, NULL);
	if (!IS_ERR(msp->clk))
		clk_prepare_enable(msp->clk);

	/*
	 * (Re-)program MBUS remapping windows if we are asked to.
	 */
	dram = mv_mbus_dram_info();
	if (dram)
		mv643xx_eth_conf_mbus_windows(msp, dram);

	ret = mv643xx_eth_shared_of_probe(pdev);
	if (ret)
		goto err_put_clk;
	pd = dev_get_platdata(&pdev->dev);

	msp->tx_csum_limit = (pd != NULL && pd->tx_csum_limit) ?
					pd->tx_csum_limit : 9 * 1024;
	infer_hw_params(msp);

	return 0;

err_put_clk:
	if (!IS_ERR(msp->clk))
		clk_disable_unprepare(msp->clk);
	return ret;
}
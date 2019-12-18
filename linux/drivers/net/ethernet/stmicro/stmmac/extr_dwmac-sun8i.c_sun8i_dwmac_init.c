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
struct sunxi_priv_data {scalar_t__ regulator; int /*<<< orphan*/  tx_clk; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  regulator_disable (scalar_t__) ; 
 int regulator_enable (scalar_t__) ; 

__attribute__((used)) static int sun8i_dwmac_init(struct platform_device *pdev, void *priv)
{
	struct sunxi_priv_data *gmac = priv;
	int ret;

	if (gmac->regulator) {
		ret = regulator_enable(gmac->regulator);
		if (ret) {
			dev_err(&pdev->dev, "Fail to enable regulator\n");
			return ret;
		}
	}

	ret = clk_prepare_enable(gmac->tx_clk);
	if (ret) {
		if (gmac->regulator)
			regulator_disable(gmac->regulator);
		dev_err(&pdev->dev, "Could not enable AHB clock\n");
		return ret;
	}

	return 0;
}
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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct mediatek_dwmac_variant {int (* dwmac_set_phy_interface ) (struct mediatek_dwmac_plat_data*) ;int (* dwmac_set_delay ) (struct mediatek_dwmac_plat_data*) ;int /*<<< orphan*/  num_clks; int /*<<< orphan*/  dma_bit_mask; } ;
struct mediatek_dwmac_plat_data {int /*<<< orphan*/  dev; int /*<<< orphan*/  clks; struct mediatek_dwmac_variant* variant; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIT_MASK (int /*<<< orphan*/ ) ; 
 int clk_bulk_prepare_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int dma_set_mask_and_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ *) ; 
 int stub1 (struct mediatek_dwmac_plat_data*) ; 
 int stub2 (struct mediatek_dwmac_plat_data*) ; 

__attribute__((used)) static int mediatek_dwmac_init(struct platform_device *pdev, void *priv)
{
	struct mediatek_dwmac_plat_data *plat = priv;
	const struct mediatek_dwmac_variant *variant = plat->variant;
	int ret;

	ret = dma_set_mask_and_coherent(plat->dev, DMA_BIT_MASK(variant->dma_bit_mask));
	if (ret) {
		dev_err(plat->dev, "No suitable DMA available, err = %d\n", ret);
		return ret;
	}

	ret = variant->dwmac_set_phy_interface(plat);
	if (ret) {
		dev_err(plat->dev, "failed to set phy interface, err = %d\n", ret);
		return ret;
	}

	ret = variant->dwmac_set_delay(plat);
	if (ret) {
		dev_err(plat->dev, "failed to set delay value, err = %d\n", ret);
		return ret;
	}

	ret = clk_bulk_prepare_enable(variant->num_clks, plat->clks);
	if (ret) {
		dev_err(plat->dev, "failed to enable clks, err = %d\n", ret);
		return ret;
	}

	pm_runtime_enable(&pdev->dev);
	pm_runtime_get_sync(&pdev->dev);

	return 0;
}
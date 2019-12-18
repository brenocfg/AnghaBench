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
struct emac_adapter {int /*<<< orphan*/ * clk; } ;

/* Variables and functions */
 size_t EMAC_CLK_AXI ; 
 size_t EMAC_CLK_CFG_AHB ; 
 size_t EMAC_CLK_HIGH_SPEED ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int clk_set_rate (int /*<<< orphan*/ ,int) ; 
 int emac_clks_get (struct platform_device*,struct emac_adapter*) ; 
 scalar_t__ has_acpi_companion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int emac_clks_phase1_init(struct platform_device *pdev,
				 struct emac_adapter *adpt)
{
	int ret;

	/* On ACPI platforms, clocks are controlled by firmware and/or
	 * ACPI, not by drivers.
	 */
	if (has_acpi_companion(&pdev->dev))
		return 0;

	ret = emac_clks_get(pdev, adpt);
	if (ret)
		return ret;

	ret = clk_prepare_enable(adpt->clk[EMAC_CLK_AXI]);
	if (ret)
		return ret;

	ret = clk_prepare_enable(adpt->clk[EMAC_CLK_CFG_AHB]);
	if (ret)
		return ret;

	ret = clk_set_rate(adpt->clk[EMAC_CLK_HIGH_SPEED], 19200000);
	if (ret)
		return ret;

	return clk_prepare_enable(adpt->clk[EMAC_CLK_HIGH_SPEED]);
}
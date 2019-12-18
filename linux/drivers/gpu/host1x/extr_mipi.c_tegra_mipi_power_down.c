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
typedef  int /*<<< orphan*/  u32 ;
struct tegra_mipi {TYPE_1__* soc; int /*<<< orphan*/  clk; } ;
struct TYPE_2__ {scalar_t__ needs_vclamp_ref; } ;

/* Variables and functions */
 int /*<<< orphan*/  MIPI_CAL_BIAS_PAD_CFG0 ; 
 int /*<<< orphan*/  MIPI_CAL_BIAS_PAD_CFG2 ; 
 int /*<<< orphan*/  MIPI_CAL_BIAS_PAD_E_VCLAMP_REF ; 
 int /*<<< orphan*/  MIPI_CAL_BIAS_PAD_PDVCLAMP ; 
 int /*<<< orphan*/  MIPI_CAL_BIAS_PAD_PDVREG ; 
 int clk_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tegra_mipi_readl (struct tegra_mipi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tegra_mipi_writel (struct tegra_mipi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tegra_mipi_power_down(struct tegra_mipi *mipi)
{
	u32 value;
	int err;

	err = clk_enable(mipi->clk);
	if (err < 0)
		return err;

	/*
	 * The MIPI_CAL_BIAS_PAD_PDVREG controls a voltage regulator that
	 * supplies the DSI pads. This must be kept enabled until none of the
	 * DSI lanes are used anymore.
	 */
	value = tegra_mipi_readl(mipi, MIPI_CAL_BIAS_PAD_CFG2);
	value |= MIPI_CAL_BIAS_PAD_PDVREG;
	tegra_mipi_writel(mipi, value, MIPI_CAL_BIAS_PAD_CFG2);

	/*
	 * MIPI_CAL_BIAS_PAD_PDVCLAMP and MIPI_CAL_BIAS_PAD_E_VCLAMP_REF
	 * control a regulator that supplies current to the pre-driver logic.
	 * Powering down this regulator causes DSI to fail, so it must remain
	 * powered on until none of the DSI lanes are used anymore.
	 */
	value = tegra_mipi_readl(mipi, MIPI_CAL_BIAS_PAD_CFG0);

	if (mipi->soc->needs_vclamp_ref)
		value &= ~MIPI_CAL_BIAS_PAD_E_VCLAMP_REF;

	value |= MIPI_CAL_BIAS_PAD_PDVCLAMP;
	tegra_mipi_writel(mipi, value, MIPI_CAL_BIAS_PAD_CFG0);

	return 0;
}
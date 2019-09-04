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
struct tegra_clk_pll {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PLLD2_MISC0_DEFAULT_VALUE ; 
 int /*<<< orphan*/  PLLD2_MISC1_CFG_DEFAULT_VALUE ; 
 int /*<<< orphan*/  PLLD2_MISC2_CTRL1_DEFAULT_VALUE ; 
 int /*<<< orphan*/  PLLD2_MISC3_CTRL2_DEFAULT_VALUE ; 
 int /*<<< orphan*/  plldss_defaults (char*,struct tegra_clk_pll*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tegra210_plld2_set_defaults(struct tegra_clk_pll *plld2)
{
	plldss_defaults("PLL_D2", plld2, PLLD2_MISC0_DEFAULT_VALUE,
			PLLD2_MISC1_CFG_DEFAULT_VALUE,
			PLLD2_MISC2_CTRL1_DEFAULT_VALUE,
			PLLD2_MISC3_CTRL2_DEFAULT_VALUE);
}
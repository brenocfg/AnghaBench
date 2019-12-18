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
struct tegra_xusb {int /*<<< orphan*/  hs_src_clk; int /*<<< orphan*/  fs_src_clk; int /*<<< orphan*/  falcon_clk; int /*<<< orphan*/  ss_clk; int /*<<< orphan*/  host_clk; int /*<<< orphan*/  pll_e; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tegra_xusb_clk_disable(struct tegra_xusb *tegra)
{
	clk_disable_unprepare(tegra->pll_e);
	clk_disable_unprepare(tegra->host_clk);
	clk_disable_unprepare(tegra->ss_clk);
	clk_disable_unprepare(tegra->falcon_clk);
	clk_disable_unprepare(tegra->fs_src_clk);
	clk_disable_unprepare(tegra->hs_src_clk);
}
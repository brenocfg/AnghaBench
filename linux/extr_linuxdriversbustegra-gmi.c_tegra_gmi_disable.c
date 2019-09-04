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
typedef  int /*<<< orphan*/  u32 ;
struct tegra_gmi {int /*<<< orphan*/  clk; int /*<<< orphan*/  rst; scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ TEGRA_GMI_CONFIG ; 
 int /*<<< orphan*/  TEGRA_GMI_CONFIG_GO ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  reset_control_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void tegra_gmi_disable(struct tegra_gmi *gmi)
{
	u32 config;

	/* stop GMI operation */
	config = readl(gmi->base + TEGRA_GMI_CONFIG);
	config &= ~TEGRA_GMI_CONFIG_GO;
	writel(config, gmi->base + TEGRA_GMI_CONFIG);

	reset_control_assert(gmi->rst);
	clk_disable_unprepare(gmi->clk);
}
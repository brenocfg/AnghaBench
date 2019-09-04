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
typedef  int u32 ;
struct tegra_dsi {struct tegra_dsi* slave; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSI_POWER_CONTROL ; 
 int DSI_POWER_CONTROL_ENABLE ; 
 int /*<<< orphan*/  DSI_TRIGGER ; 
 int tegra_dsi_readl (struct tegra_dsi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tegra_dsi_writel (struct tegra_dsi*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void tegra_dsi_soft_reset(struct tegra_dsi *dsi)
{
	u32 value;

	value = tegra_dsi_readl(dsi, DSI_POWER_CONTROL);
	value &= ~DSI_POWER_CONTROL_ENABLE;
	tegra_dsi_writel(dsi, value, DSI_POWER_CONTROL);

	usleep_range(300, 1000);

	value = tegra_dsi_readl(dsi, DSI_POWER_CONTROL);
	value |= DSI_POWER_CONTROL_ENABLE;
	tegra_dsi_writel(dsi, value, DSI_POWER_CONTROL);

	usleep_range(300, 1000);

	value = tegra_dsi_readl(dsi, DSI_TRIGGER);
	if (value)
		tegra_dsi_writel(dsi, 0, DSI_TRIGGER);

	if (dsi->slave)
		tegra_dsi_soft_reset(dsi->slave);
}
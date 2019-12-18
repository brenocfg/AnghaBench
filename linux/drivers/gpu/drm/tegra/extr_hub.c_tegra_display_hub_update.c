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
struct tegra_dc {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int COMMON_ACTREQ ; 
 int COMMON_UPDATE ; 
 int CURS_SLOTS (int) ; 
 int /*<<< orphan*/  DC_CMD_IHUB_COMMON_MISC_CTL ; 
 int /*<<< orphan*/  DC_CMD_STATE_CONTROL ; 
 int /*<<< orphan*/  DC_DISP_IHUB_COMMON_DISPLAY_FETCH_METER ; 
 int LATENCY_EVENT ; 
 int WGRP_SLOTS (int) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ ) ; 
 int tegra_dc_readl (struct tegra_dc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tegra_dc_writel (struct tegra_dc*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tegra_display_hub_update(struct tegra_dc *dc)
{
	u32 value;

	pm_runtime_get_sync(dc->dev);

	value = tegra_dc_readl(dc, DC_CMD_IHUB_COMMON_MISC_CTL);
	value &= ~LATENCY_EVENT;
	tegra_dc_writel(dc, value, DC_CMD_IHUB_COMMON_MISC_CTL);

	value = tegra_dc_readl(dc, DC_DISP_IHUB_COMMON_DISPLAY_FETCH_METER);
	value = CURS_SLOTS(1) | WGRP_SLOTS(1);
	tegra_dc_writel(dc, value, DC_DISP_IHUB_COMMON_DISPLAY_FETCH_METER);

	tegra_dc_writel(dc, COMMON_UPDATE, DC_CMD_STATE_CONTROL);
	tegra_dc_readl(dc, DC_CMD_STATE_CONTROL);
	tegra_dc_writel(dc, COMMON_ACTREQ, DC_CMD_STATE_CONTROL);
	tegra_dc_readl(dc, DC_CMD_STATE_CONTROL);

	pm_runtime_put(dc->dev);
}
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
struct tegra_dc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DC_CMD_DISPLAY_COMMAND ; 
 int /*<<< orphan*/  DISP_CTRL_MODE_MASK ; 
 int /*<<< orphan*/  tegra_dc_commit (struct tegra_dc*) ; 
 int /*<<< orphan*/  tegra_dc_readl (struct tegra_dc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tegra_dc_writel (struct tegra_dc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tegra_dc_stop(struct tegra_dc *dc)
{
	u32 value;

	/* stop the display controller */
	value = tegra_dc_readl(dc, DC_CMD_DISPLAY_COMMAND);
	value &= ~DISP_CTRL_MODE_MASK;
	tegra_dc_writel(dc, value, DC_CMD_DISPLAY_COMMAND);

	tegra_dc_commit(dc);
}
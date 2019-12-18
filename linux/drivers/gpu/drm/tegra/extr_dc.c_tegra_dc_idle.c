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
struct tegra_dc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DC_CMD_DISPLAY_COMMAND ; 
 int DISP_CTRL_MODE_MASK ; 
 int tegra_dc_readl_active (struct tegra_dc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool tegra_dc_idle(struct tegra_dc *dc)
{
	u32 value;

	value = tegra_dc_readl_active(dc, DC_CMD_DISPLAY_COMMAND);

	return (value & DISP_CTRL_MODE_MASK) == 0;
}
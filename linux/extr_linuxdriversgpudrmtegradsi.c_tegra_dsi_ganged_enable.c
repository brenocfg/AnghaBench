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
typedef  unsigned int u32 ;
struct tegra_dsi {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSI_GANGED_MODE_CONTROL ; 
 unsigned int DSI_GANGED_MODE_CONTROL_ENABLE ; 
 int /*<<< orphan*/  DSI_GANGED_MODE_SIZE ; 
 int /*<<< orphan*/  DSI_GANGED_MODE_START ; 
 int /*<<< orphan*/  tegra_dsi_writel (struct tegra_dsi*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tegra_dsi_ganged_enable(struct tegra_dsi *dsi, unsigned int start,
				    unsigned int size)
{
	u32 value;

	tegra_dsi_writel(dsi, start, DSI_GANGED_MODE_START);
	tegra_dsi_writel(dsi, size << 16 | size, DSI_GANGED_MODE_SIZE);

	value = DSI_GANGED_MODE_CONTROL_ENABLE;
	tegra_dsi_writel(dsi, value, DSI_GANGED_MODE_CONTROL);
}
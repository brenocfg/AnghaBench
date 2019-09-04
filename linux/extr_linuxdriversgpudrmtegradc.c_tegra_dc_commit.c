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
struct tegra_dc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DC_CMD_STATE_CONTROL ; 
 int GENERAL_ACT_REQ ; 
 int /*<<< orphan*/  tegra_dc_writel (struct tegra_dc*,int,int /*<<< orphan*/ ) ; 

void tegra_dc_commit(struct tegra_dc *dc)
{
	tegra_dc_writel(dc, GENERAL_ACT_REQ << 8, DC_CMD_STATE_CONTROL);
	tegra_dc_writel(dc, GENERAL_ACT_REQ, DC_CMD_STATE_CONTROL);
}
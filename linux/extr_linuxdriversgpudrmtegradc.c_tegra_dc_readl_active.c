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
 int /*<<< orphan*/  DC_CMD_STATE_ACCESS ; 
 int /*<<< orphan*/  READ_MUX ; 
 int /*<<< orphan*/  tegra_dc_readl (struct tegra_dc*,unsigned long) ; 
 int /*<<< orphan*/  tegra_dc_writel (struct tegra_dc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 tegra_dc_readl_active(struct tegra_dc *dc, unsigned long offset)
{
	u32 value;

	tegra_dc_writel(dc, READ_MUX, DC_CMD_STATE_ACCESS);
	value = tegra_dc_readl(dc, offset);
	tegra_dc_writel(dc, 0, DC_CMD_STATE_ACCESS);

	return value;
}
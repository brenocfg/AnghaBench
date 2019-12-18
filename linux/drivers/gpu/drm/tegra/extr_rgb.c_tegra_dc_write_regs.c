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
struct reg_entry {int /*<<< orphan*/  offset; int /*<<< orphan*/  value; } ;

/* Variables and functions */
 int /*<<< orphan*/  tegra_dc_writel (struct tegra_dc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tegra_dc_write_regs(struct tegra_dc *dc,
				const struct reg_entry *table,
				unsigned int num)
{
	unsigned int i;

	for (i = 0; i < num; i++)
		tegra_dc_writel(dc, table[i].value, table[i].offset);
}
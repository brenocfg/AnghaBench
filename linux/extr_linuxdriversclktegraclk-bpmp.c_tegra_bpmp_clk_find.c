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
struct tegra_bpmp_clk_info {unsigned int id; } ;

/* Variables and functions */

__attribute__((used)) static const struct tegra_bpmp_clk_info *
tegra_bpmp_clk_find(const struct tegra_bpmp_clk_info *clocks,
		    unsigned int num_clocks, unsigned int id)
{
	unsigned int i;

	for (i = 0; i < num_clocks; i++)
		if (clocks[i].id == id)
			return &clocks[i];

	return NULL;
}
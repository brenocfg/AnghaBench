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
struct rockchip_cpuclk_rate_table {unsigned long prate; } ;
struct rockchip_cpuclk {int rate_count; struct rockchip_cpuclk_rate_table* rate_table; } ;

/* Variables and functions */

__attribute__((used)) static const struct rockchip_cpuclk_rate_table *rockchip_get_cpuclk_settings(
			    struct rockchip_cpuclk *cpuclk, unsigned long rate)
{
	const struct rockchip_cpuclk_rate_table *rate_table =
							cpuclk->rate_table;
	int i;

	for (i = 0; i < cpuclk->rate_count; i++) {
		if (rate == rate_table[i].prate)
			return &rate_table[i];
	}

	return NULL;
}
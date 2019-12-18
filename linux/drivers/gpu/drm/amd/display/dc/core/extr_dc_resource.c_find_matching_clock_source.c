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
struct resource_pool {int clk_src_count; struct clock_source** clock_sources; } ;
struct clock_source {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int find_matching_clock_source(
		const struct resource_pool *pool,
		struct clock_source *clock_source)
{

	int i;

	for (i = 0; i < pool->clk_src_count; i++) {
		if (pool->clock_sources[i] == clock_source)
			return i;
	}
	return -1;
}
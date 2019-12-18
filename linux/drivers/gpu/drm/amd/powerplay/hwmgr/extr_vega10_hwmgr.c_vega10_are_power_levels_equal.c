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
struct vega10_performance_level {scalar_t__ soc_clock; scalar_t__ gfx_clock; scalar_t__ mem_clock; } ;

/* Variables and functions */

__attribute__((used)) static inline bool vega10_are_power_levels_equal(
				const struct vega10_performance_level *pl1,
				const struct vega10_performance_level *pl2)
{
	return ((pl1->soc_clock == pl2->soc_clock) &&
			(pl1->gfx_clock == pl2->gfx_clock) &&
			(pl1->mem_clock == pl2->mem_clock));
}
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
struct smu7_performance_level {scalar_t__ memory_clock; scalar_t__ engine_clock; scalar_t__ pcie_gen; scalar_t__ pcie_lane; } ;

/* Variables and functions */

__attribute__((used)) static inline bool smu7_are_power_levels_equal(const struct smu7_performance_level *pl1,
							   const struct smu7_performance_level *pl2)
{
	return ((pl1->memory_clock == pl2->memory_clock) &&
		  (pl1->engine_clock == pl2->engine_clock) &&
		  (pl1->pcie_gen == pl2->pcie_gen) &&
		  (pl1->pcie_lane == pl2->pcie_lane));
}
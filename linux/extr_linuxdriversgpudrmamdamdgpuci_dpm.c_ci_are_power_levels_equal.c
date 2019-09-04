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
struct ci_pl {scalar_t__ mclk; scalar_t__ sclk; scalar_t__ pcie_gen; scalar_t__ pcie_lane; } ;

/* Variables and functions */

__attribute__((used)) static inline bool ci_are_power_levels_equal(const struct ci_pl *ci_cpl1,
						const struct ci_pl *ci_cpl2)
{
	return ((ci_cpl1->mclk == ci_cpl2->mclk) &&
		  (ci_cpl1->sclk == ci_cpl2->sclk) &&
		  (ci_cpl1->pcie_gen == ci_cpl2->pcie_gen) &&
		  (ci_cpl1->pcie_lane == ci_cpl2->pcie_lane));
}
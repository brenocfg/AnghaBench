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
struct rv7xx_pl {scalar_t__ mclk; scalar_t__ sclk; scalar_t__ pcie_gen; scalar_t__ vddc; scalar_t__ vddci; } ;

/* Variables and functions */

__attribute__((used)) static inline bool si_are_power_levels_equal(const struct rv7xx_pl  *si_cpl1,
						const struct rv7xx_pl *si_cpl2)
{
	return ((si_cpl1->mclk == si_cpl2->mclk) &&
		  (si_cpl1->sclk == si_cpl2->sclk) &&
		  (si_cpl1->pcie_gen == si_cpl2->pcie_gen) &&
		  (si_cpl1->vddc == si_cpl2->vddc) &&
		  (si_cpl1->vddci == si_cpl2->vddci));
}
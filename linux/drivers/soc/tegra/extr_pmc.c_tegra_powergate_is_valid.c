#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct tegra_pmc {TYPE_1__* soc; } ;
struct TYPE_2__ {scalar_t__* powergates; } ;

/* Variables and functions */

__attribute__((used)) static inline bool tegra_powergate_is_valid(struct tegra_pmc *pmc, int id)
{
	return (pmc->soc && pmc->soc->powergates[id]);
}
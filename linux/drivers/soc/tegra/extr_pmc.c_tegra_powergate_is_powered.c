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
struct tegra_pmc {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  tegra_powergate_is_valid (struct tegra_pmc*,unsigned int) ; 
 int tegra_powergate_state (unsigned int) ; 

__attribute__((used)) static int tegra_powergate_is_powered(struct tegra_pmc *pmc, unsigned int id)
{
	if (!tegra_powergate_is_valid(pmc, id))
		return -EINVAL;

	return tegra_powergate_state(id);
}
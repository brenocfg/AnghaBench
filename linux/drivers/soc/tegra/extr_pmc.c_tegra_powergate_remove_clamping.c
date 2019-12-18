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

/* Variables and functions */
 int EINVAL ; 
 int __tegra_powergate_remove_clamping (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  pmc ; 
 int /*<<< orphan*/  tegra_powergate_is_available (int /*<<< orphan*/ ,unsigned int) ; 

int tegra_powergate_remove_clamping(unsigned int id)
{
	if (!tegra_powergate_is_available(pmc, id))
		return -EINVAL;

	return __tegra_powergate_remove_clamping(pmc, id);
}
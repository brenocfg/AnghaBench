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
struct trinity_ps {int num_levels; int /*<<< orphan*/ * levels; scalar_t__ bapm_flags; scalar_t__ nbps_flags; } ;
struct trinity_power_info {int /*<<< orphan*/  boot_pl; } ;
struct radeon_device {int dummy; } ;

/* Variables and functions */
 struct trinity_power_info* trinity_get_pi (struct radeon_device*) ; 

__attribute__((used)) static void trinity_patch_boot_state(struct radeon_device *rdev,
				     struct trinity_ps *ps)
{
	struct trinity_power_info *pi = trinity_get_pi(rdev);

	ps->num_levels = 1;
	ps->nbps_flags = 0;
	ps->bapm_flags = 0;
	ps->levels[0] = pi->boot_pl;
}
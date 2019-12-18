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
typedef  scalar_t__ u16 ;
struct radeon_ps {int dummy; } ;
struct radeon_device {int dummy; } ;
struct ni_ps {int performance_level_count; TYPE_1__* performance_levels; } ;
typedef  enum radeon_pcie_gen { ____Placeholder_radeon_pcie_gen } radeon_pcie_gen ;
struct TYPE_2__ {scalar_t__ pcie_gen; } ;

/* Variables and functions */
 struct ni_ps* ni_get_ps (struct radeon_ps*) ; 

__attribute__((used)) static enum radeon_pcie_gen si_get_maximum_link_speed(struct radeon_device *rdev,
						      struct radeon_ps *radeon_state)
{
	struct ni_ps *state = ni_get_ps(radeon_state);
	int i;
	u16 pcie_speed, max_speed = 0;

	for (i = 0; i < state->performance_level_count; i++) {
		pcie_speed = state->performance_levels[i].pcie_gen;
		if (max_speed < pcie_speed)
			max_speed = pcie_speed;
	}
	return max_speed;
}
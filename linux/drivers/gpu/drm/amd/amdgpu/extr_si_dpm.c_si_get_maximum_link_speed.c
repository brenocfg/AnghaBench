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
struct si_ps {int performance_level_count; TYPE_1__* performance_levels; } ;
struct amdgpu_ps {int dummy; } ;
struct amdgpu_device {int dummy; } ;
typedef  enum amdgpu_pcie_gen { ____Placeholder_amdgpu_pcie_gen } amdgpu_pcie_gen ;
struct TYPE_2__ {scalar_t__ pcie_gen; } ;

/* Variables and functions */
 struct si_ps* si_get_ps (struct amdgpu_ps*) ; 

__attribute__((used)) static enum amdgpu_pcie_gen si_get_maximum_link_speed(struct amdgpu_device *adev,
						      struct amdgpu_ps *amdgpu_state)
{
	struct si_ps *state = si_get_ps(amdgpu_state);
	int i;
	u16 pcie_speed, max_speed = 0;

	for (i = 0; i < state->performance_level_count; i++) {
		pcie_speed = state->performance_levels[i].pcie_gen;
		if (max_speed < pcie_speed)
			max_speed = pcie_speed;
	}
	return max_speed;
}
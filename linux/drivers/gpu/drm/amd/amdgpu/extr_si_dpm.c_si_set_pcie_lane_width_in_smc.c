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
typedef  scalar_t__ u32 ;
struct amdgpu_ps {int caps; } ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int ATOM_PPLIB_PCIE_LINK_WIDTH_MASK ; 
 int ATOM_PPLIB_PCIE_LINK_WIDTH_SHIFT ; 
 int /*<<< orphan*/  SI_SMC_SOFT_REGISTER_non_ulv_pcie_link_width ; 
 scalar_t__ amdgpu_get_pcie_lanes (struct amdgpu_device*) ; 
 int /*<<< orphan*/  amdgpu_set_pcie_lanes (struct amdgpu_device*,scalar_t__) ; 
 int /*<<< orphan*/  si_write_smc_soft_register (struct amdgpu_device*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void si_set_pcie_lane_width_in_smc(struct amdgpu_device *adev,
					  struct amdgpu_ps *amdgpu_new_state,
					  struct amdgpu_ps *amdgpu_current_state)
{
	u32 lane_width;
	u32 new_lane_width =
		((amdgpu_new_state->caps & ATOM_PPLIB_PCIE_LINK_WIDTH_MASK) >> ATOM_PPLIB_PCIE_LINK_WIDTH_SHIFT) + 1;
	u32 current_lane_width =
		((amdgpu_current_state->caps & ATOM_PPLIB_PCIE_LINK_WIDTH_MASK) >> ATOM_PPLIB_PCIE_LINK_WIDTH_SHIFT) + 1;

	if (new_lane_width != current_lane_width) {
		amdgpu_set_pcie_lanes(adev, new_lane_width);
		lane_width = amdgpu_get_pcie_lanes(adev);
		si_write_smc_soft_register(adev, SI_SMC_SOFT_REGISTER_non_ulv_pcie_link_width, lane_width);
	}
}
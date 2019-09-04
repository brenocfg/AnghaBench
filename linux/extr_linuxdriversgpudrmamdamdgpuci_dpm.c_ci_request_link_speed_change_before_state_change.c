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
struct ci_power_info {scalar_t__ force_pcie_gen; int pspp_notify_required; } ;
struct amdgpu_ps {int dummy; } ;
struct amdgpu_device {int dummy; } ;
typedef  enum amdgpu_pcie_gen { ____Placeholder_amdgpu_pcie_gen } amdgpu_pcie_gen ;

/* Variables and functions */
 scalar_t__ AMDGPU_PCIE_GEN_INVALID ; 
 int ci_get_current_pcie_speed (struct amdgpu_device*) ; 
 int ci_get_maximum_link_speed (struct amdgpu_device*,struct amdgpu_ps*) ; 
 struct ci_power_info* ci_get_pi (struct amdgpu_device*) ; 

__attribute__((used)) static void ci_request_link_speed_change_before_state_change(struct amdgpu_device *adev,
							     struct amdgpu_ps *amdgpu_new_state,
							     struct amdgpu_ps *amdgpu_current_state)
{
	struct ci_power_info *pi = ci_get_pi(adev);
	enum amdgpu_pcie_gen target_link_speed =
		ci_get_maximum_link_speed(adev, amdgpu_new_state);
	enum amdgpu_pcie_gen current_link_speed;

	if (pi->force_pcie_gen == AMDGPU_PCIE_GEN_INVALID)
		current_link_speed = ci_get_maximum_link_speed(adev, amdgpu_current_state);
	else
		current_link_speed = pi->force_pcie_gen;

	pi->force_pcie_gen = AMDGPU_PCIE_GEN_INVALID;
	pi->pspp_notify_required = false;
	if (target_link_speed > current_link_speed) {
		switch (target_link_speed) {
#ifdef CONFIG_ACPI
		case AMDGPU_PCIE_GEN3:
			if (amdgpu_acpi_pcie_performance_request(adev, PCIE_PERF_REQ_PECI_GEN3, false) == 0)
				break;
			pi->force_pcie_gen = AMDGPU_PCIE_GEN2;
			if (current_link_speed == AMDGPU_PCIE_GEN2)
				break;
		case AMDGPU_PCIE_GEN2:
			if (amdgpu_acpi_pcie_performance_request(adev, PCIE_PERF_REQ_PECI_GEN2, false) == 0)
				break;
#endif
		default:
			pi->force_pcie_gen = ci_get_current_pcie_speed(adev);
			break;
		}
	} else {
		if (target_link_speed < current_link_speed)
			pi->pspp_notify_required = true;
	}
}
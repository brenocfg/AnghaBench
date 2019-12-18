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
struct si_power_info {scalar_t__ force_pcie_gen; int pspp_notify_required; } ;
struct amdgpu_ps {int dummy; } ;
struct amdgpu_device {int dummy; } ;
typedef  enum amdgpu_pcie_gen { ____Placeholder_amdgpu_pcie_gen } amdgpu_pcie_gen ;

/* Variables and functions */
#define  AMDGPU_PCIE_GEN2 129 
#define  AMDGPU_PCIE_GEN3 128 
 scalar_t__ AMDGPU_PCIE_GEN_INVALID ; 
 int /*<<< orphan*/  PCIE_PERF_REQ_PECI_GEN2 ; 
 int /*<<< orphan*/  PCIE_PERF_REQ_PECI_GEN3 ; 
 int /*<<< orphan*/  amdgpu_acpi_pcie_performance_request (struct amdgpu_device*,int /*<<< orphan*/ ,int) ; 
 int si_get_current_pcie_speed (struct amdgpu_device*) ; 
 int si_get_maximum_link_speed (struct amdgpu_device*,struct amdgpu_ps*) ; 
 struct si_power_info* si_get_pi (struct amdgpu_device*) ; 

__attribute__((used)) static void si_request_link_speed_change_before_state_change(struct amdgpu_device *adev,
							     struct amdgpu_ps *amdgpu_new_state,
							     struct amdgpu_ps *amdgpu_current_state)
{
	struct si_power_info *si_pi = si_get_pi(adev);
	enum amdgpu_pcie_gen target_link_speed = si_get_maximum_link_speed(adev, amdgpu_new_state);
	enum amdgpu_pcie_gen current_link_speed;

	if (si_pi->force_pcie_gen == AMDGPU_PCIE_GEN_INVALID)
		current_link_speed = si_get_maximum_link_speed(adev, amdgpu_current_state);
	else
		current_link_speed = si_pi->force_pcie_gen;

	si_pi->force_pcie_gen = AMDGPU_PCIE_GEN_INVALID;
	si_pi->pspp_notify_required = false;
	if (target_link_speed > current_link_speed) {
		switch (target_link_speed) {
#if defined(CONFIG_ACPI)
		case AMDGPU_PCIE_GEN3:
			if (amdgpu_acpi_pcie_performance_request(adev, PCIE_PERF_REQ_PECI_GEN3, false) == 0)
				break;
			si_pi->force_pcie_gen = AMDGPU_PCIE_GEN2;
			if (current_link_speed == AMDGPU_PCIE_GEN2)
				break;
			/* fall through */
		case AMDGPU_PCIE_GEN2:
			if (amdgpu_acpi_pcie_performance_request(adev, PCIE_PERF_REQ_PECI_GEN2, false) == 0)
				break;
#endif
			/* fall through */
		default:
			si_pi->force_pcie_gen = si_get_current_pcie_speed(adev);
			break;
		}
	} else {
		if (target_link_speed < current_link_speed)
			si_pi->pspp_notify_required = true;
	}
}
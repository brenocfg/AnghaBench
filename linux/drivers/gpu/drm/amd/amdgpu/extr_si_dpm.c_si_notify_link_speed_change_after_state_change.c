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
typedef  scalar_t__ u8 ;
struct si_power_info {scalar_t__ pspp_notify_required; } ;
struct amdgpu_ps {int dummy; } ;
struct amdgpu_device {int dummy; } ;
typedef  enum amdgpu_pcie_gen { ____Placeholder_amdgpu_pcie_gen } amdgpu_pcie_gen ;

/* Variables and functions */
 int AMDGPU_PCIE_GEN2 ; 
 int AMDGPU_PCIE_GEN3 ; 
 scalar_t__ PCIE_PERF_REQ_PECI_GEN1 ; 
 scalar_t__ PCIE_PERF_REQ_PECI_GEN2 ; 
 scalar_t__ PCIE_PERF_REQ_PECI_GEN3 ; 
 int /*<<< orphan*/  amdgpu_acpi_pcie_performance_request (struct amdgpu_device*,scalar_t__,int) ; 
 scalar_t__ si_get_current_pcie_speed (struct amdgpu_device*) ; 
 int si_get_maximum_link_speed (struct amdgpu_device*,struct amdgpu_ps*) ; 
 struct si_power_info* si_get_pi (struct amdgpu_device*) ; 

__attribute__((used)) static void si_notify_link_speed_change_after_state_change(struct amdgpu_device *adev,
							   struct amdgpu_ps *amdgpu_new_state,
							   struct amdgpu_ps *amdgpu_current_state)
{
	struct si_power_info *si_pi = si_get_pi(adev);
	enum amdgpu_pcie_gen target_link_speed = si_get_maximum_link_speed(adev, amdgpu_new_state);
	u8 request;

	if (si_pi->pspp_notify_required) {
		if (target_link_speed == AMDGPU_PCIE_GEN3)
			request = PCIE_PERF_REQ_PECI_GEN3;
		else if (target_link_speed == AMDGPU_PCIE_GEN2)
			request = PCIE_PERF_REQ_PECI_GEN2;
		else
			request = PCIE_PERF_REQ_PECI_GEN1;

		if ((request == PCIE_PERF_REQ_PECI_GEN1) &&
		    (si_get_current_pcie_speed(adev) > 0))
			return;

#if defined(CONFIG_ACPI)
		amdgpu_acpi_pcie_performance_request(adev, request, false);
#endif
	}
}
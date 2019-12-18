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
struct radeon_ps {int dummy; } ;
struct radeon_device {int dummy; } ;
typedef  enum radeon_pcie_gen { ____Placeholder_radeon_pcie_gen } radeon_pcie_gen ;

/* Variables and functions */
 scalar_t__ PCIE_PERF_REQ_PECI_GEN1 ; 
 scalar_t__ PCIE_PERF_REQ_PECI_GEN2 ; 
 scalar_t__ PCIE_PERF_REQ_PECI_GEN3 ; 
 int RADEON_PCIE_GEN2 ; 
 int RADEON_PCIE_GEN3 ; 
 int /*<<< orphan*/  radeon_acpi_pcie_performance_request (struct radeon_device*,scalar_t__,int) ; 
 scalar_t__ si_get_current_pcie_speed (struct radeon_device*) ; 
 int si_get_maximum_link_speed (struct radeon_device*,struct radeon_ps*) ; 
 struct si_power_info* si_get_pi (struct radeon_device*) ; 

__attribute__((used)) static void si_notify_link_speed_change_after_state_change(struct radeon_device *rdev,
							   struct radeon_ps *radeon_new_state,
							   struct radeon_ps *radeon_current_state)
{
	struct si_power_info *si_pi = si_get_pi(rdev);
	enum radeon_pcie_gen target_link_speed = si_get_maximum_link_speed(rdev, radeon_new_state);
	u8 request;

	if (si_pi->pspp_notify_required) {
		if (target_link_speed == RADEON_PCIE_GEN3)
			request = PCIE_PERF_REQ_PECI_GEN3;
		else if (target_link_speed == RADEON_PCIE_GEN2)
			request = PCIE_PERF_REQ_PECI_GEN2;
		else
			request = PCIE_PERF_REQ_PECI_GEN1;

		if ((request == PCIE_PERF_REQ_PECI_GEN1) &&
		    (si_get_current_pcie_speed(rdev) > 0))
			return;

#if defined(CONFIG_ACPI)
		radeon_acpi_pcie_performance_request(rdev, request, false);
#endif
	}
}
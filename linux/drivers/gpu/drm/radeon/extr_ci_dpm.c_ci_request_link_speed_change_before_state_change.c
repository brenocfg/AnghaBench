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
struct radeon_ps {int dummy; } ;
struct radeon_device {int dummy; } ;
struct ci_power_info {scalar_t__ force_pcie_gen; int pspp_notify_required; } ;
typedef  enum radeon_pcie_gen { ____Placeholder_radeon_pcie_gen } radeon_pcie_gen ;

/* Variables and functions */
 int /*<<< orphan*/  PCIE_PERF_REQ_PECI_GEN2 ; 
 int /*<<< orphan*/  PCIE_PERF_REQ_PECI_GEN3 ; 
#define  RADEON_PCIE_GEN2 129 
#define  RADEON_PCIE_GEN3 128 
 scalar_t__ RADEON_PCIE_GEN_INVALID ; 
 int ci_get_current_pcie_speed (struct radeon_device*) ; 
 int ci_get_maximum_link_speed (struct radeon_device*,struct radeon_ps*) ; 
 struct ci_power_info* ci_get_pi (struct radeon_device*) ; 
 int /*<<< orphan*/  radeon_acpi_pcie_performance_request (struct radeon_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ci_request_link_speed_change_before_state_change(struct radeon_device *rdev,
							     struct radeon_ps *radeon_new_state,
							     struct radeon_ps *radeon_current_state)
{
	struct ci_power_info *pi = ci_get_pi(rdev);
	enum radeon_pcie_gen target_link_speed =
		ci_get_maximum_link_speed(rdev, radeon_new_state);
	enum radeon_pcie_gen current_link_speed;

	if (pi->force_pcie_gen == RADEON_PCIE_GEN_INVALID)
		current_link_speed = ci_get_maximum_link_speed(rdev, radeon_current_state);
	else
		current_link_speed = pi->force_pcie_gen;

	pi->force_pcie_gen = RADEON_PCIE_GEN_INVALID;
	pi->pspp_notify_required = false;
	if (target_link_speed > current_link_speed) {
		switch (target_link_speed) {
#ifdef CONFIG_ACPI
		case RADEON_PCIE_GEN3:
			if (radeon_acpi_pcie_performance_request(rdev, PCIE_PERF_REQ_PECI_GEN3, false) == 0)
				break;
			pi->force_pcie_gen = RADEON_PCIE_GEN2;
			if (current_link_speed == RADEON_PCIE_GEN2)
				break;
			/* fall through */
		case RADEON_PCIE_GEN2:
			if (radeon_acpi_pcie_performance_request(rdev, PCIE_PERF_REQ_PECI_GEN2, false) == 0)
				break;
#endif
			/* fall through */
		default:
			pi->force_pcie_gen = ci_get_current_pcie_speed(rdev);
			break;
		}
	} else {
		if (target_link_speed < current_link_speed)
			pi->pspp_notify_required = true;
	}
}
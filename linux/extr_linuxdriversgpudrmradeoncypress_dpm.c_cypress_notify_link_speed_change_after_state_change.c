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
typedef  int /*<<< orphan*/  u8 ;
struct radeon_ps {int dummy; } ;
struct radeon_device {int dummy; } ;
typedef  enum radeon_pcie_gen { ____Placeholder_radeon_pcie_gen } radeon_pcie_gen ;

/* Variables and functions */
 int /*<<< orphan*/  PCIE_PERF_REQ_PECI_GEN1 ; 
 int /*<<< orphan*/  PCIE_PERF_REQ_PECI_GEN2 ; 
 int /*<<< orphan*/  PCIE_PERF_REQ_PECI_GEN3 ; 
 int RADEON_PCIE_GEN1 ; 
 int RADEON_PCIE_GEN2 ; 
 int cypress_get_maximum_link_speed (struct radeon_ps*) ; 
 int /*<<< orphan*/  cypress_pcie_performance_request (struct radeon_device*,int /*<<< orphan*/ ,int) ; 

void cypress_notify_link_speed_change_after_state_change(struct radeon_device *rdev,
							 struct radeon_ps *radeon_new_state,
							 struct radeon_ps *radeon_current_state)
{
	enum radeon_pcie_gen pcie_link_speed_target =
		cypress_get_maximum_link_speed(radeon_new_state);
	enum radeon_pcie_gen pcie_link_speed_current =
		cypress_get_maximum_link_speed(radeon_current_state);
	u8 request;

	if (pcie_link_speed_target < pcie_link_speed_current) {
		if (pcie_link_speed_target == RADEON_PCIE_GEN1)
			request = PCIE_PERF_REQ_PECI_GEN1;
		else if (pcie_link_speed_target == RADEON_PCIE_GEN2)
			request = PCIE_PERF_REQ_PECI_GEN2;
		else
			request = PCIE_PERF_REQ_PECI_GEN3;

		cypress_pcie_performance_request(rdev, request, false);
	}
}
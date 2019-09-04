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
struct radeon_device {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int ni_pcie_performance_request(struct radeon_device *rdev,
				       u8 perf_req, bool advertise)
{
#if defined(CONFIG_ACPI)
	struct evergreen_power_info *eg_pi = evergreen_get_pi(rdev);

	if ((perf_req == PCIE_PERF_REQ_PECI_GEN1) ||
	    (perf_req == PCIE_PERF_REQ_PECI_GEN2)) {
		if (eg_pi->pcie_performance_request_registered == false)
			radeon_acpi_pcie_notify_device_ready(rdev);
		eg_pi->pcie_performance_request_registered = true;
		return radeon_acpi_pcie_performance_request(rdev, perf_req, advertise);
	} else if ((perf_req == PCIE_PERF_REQ_REMOVE_REGISTRY) &&
		    eg_pi->pcie_performance_request_registered) {
		eg_pi->pcie_performance_request_registered = false;
		return radeon_acpi_pcie_performance_request(rdev, perf_req, advertise);
	}
#endif
	return 0;
}
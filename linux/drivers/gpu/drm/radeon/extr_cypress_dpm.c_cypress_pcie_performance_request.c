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
typedef  int u32 ;
struct radeon_device {int dummy; } ;
struct evergreen_power_info {int pcie_performance_request_registered; } ;

/* Variables and functions */
 int LC_CURRENT_DATA_RATE ; 
 int /*<<< orphan*/  PCIE_LC_SPEED_CNTL ; 
 scalar_t__ PCIE_PERF_REQ_PECI_GEN1 ; 
 scalar_t__ PCIE_PERF_REQ_PECI_GEN2 ; 
 scalar_t__ PCIE_PERF_REQ_REMOVE_REGISTRY ; 
 int RREG32_PCIE_PORT (int /*<<< orphan*/ ) ; 
 struct evergreen_power_info* evergreen_get_pi (struct radeon_device*) ; 
 int radeon_acpi_pcie_performance_request (struct radeon_device*,scalar_t__,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int cypress_pcie_performance_request(struct radeon_device *rdev,
					    u8 perf_req, bool advertise)
{
#if defined(CONFIG_ACPI)
	struct evergreen_power_info *eg_pi = evergreen_get_pi(rdev);
#endif
	u32 tmp;

	udelay(10);
	tmp = RREG32_PCIE_PORT(PCIE_LC_SPEED_CNTL);
	if ((perf_req == PCIE_PERF_REQ_PECI_GEN1) && (tmp & LC_CURRENT_DATA_RATE))
		return 0;

#if defined(CONFIG_ACPI)
	if ((perf_req == PCIE_PERF_REQ_PECI_GEN1) ||
	    (perf_req == PCIE_PERF_REQ_PECI_GEN2)) {
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
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
struct TYPE_2__ {scalar_t__ pcie_dev_rdy; scalar_t__ pcie_perf_req; } ;
struct radeon_atcs {TYPE_1__ functions; } ;
struct radeon_device {struct radeon_atcs atcs; } ;

/* Variables and functions */

bool radeon_acpi_is_pcie_performance_request_supported(struct radeon_device *rdev)
{
	struct radeon_atcs *atcs = &rdev->atcs;

	if (atcs->functions.pcie_perf_req && atcs->functions.pcie_dev_rdy)
		return true;

	return false;
}
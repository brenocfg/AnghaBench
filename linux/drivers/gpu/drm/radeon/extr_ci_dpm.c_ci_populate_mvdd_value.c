#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct TYPE_13__ {size_t count; TYPE_1__* entries; } ;
struct TYPE_14__ {TYPE_4__ mvdd_dependency_on_mclk; } ;
struct TYPE_15__ {TYPE_5__ dyn_state; } ;
struct TYPE_16__ {TYPE_6__ dpm; } ;
struct radeon_device {TYPE_7__ pm; } ;
struct TYPE_12__ {TYPE_2__* entries; } ;
struct ci_power_info {scalar_t__ mvdd_control; TYPE_3__ mvdd_voltage_table; } ;
struct TYPE_17__ {int /*<<< orphan*/  Voltage; } ;
struct TYPE_11__ {int /*<<< orphan*/  value; } ;
struct TYPE_10__ {size_t clk; } ;
typedef  TYPE_8__ SMU7_Discrete_VoltageLevel ;

/* Variables and functions */
 scalar_t__ CISLANDS_VOLTAGE_CONTROL_NONE ; 
 int EINVAL ; 
 struct ci_power_info* ci_get_pi (struct radeon_device*) ; 

__attribute__((used)) static int ci_populate_mvdd_value(struct radeon_device *rdev, u32 mclk,
				  SMU7_Discrete_VoltageLevel *voltage)
{
	struct ci_power_info *pi = ci_get_pi(rdev);
	u32 i = 0;

	if (pi->mvdd_control != CISLANDS_VOLTAGE_CONTROL_NONE) {
		for (i = 0; i < rdev->pm.dpm.dyn_state.mvdd_dependency_on_mclk.count; i++) {
			if (mclk <= rdev->pm.dpm.dyn_state.mvdd_dependency_on_mclk.entries[i].clk) {
				voltage->Voltage = pi->mvdd_voltage_table.entries[i].value;
				break;
			}
		}

		if (i >= rdev->pm.dpm.dyn_state.mvdd_dependency_on_mclk.count)
			return -EINVAL;
	}

	return -EINVAL;
}
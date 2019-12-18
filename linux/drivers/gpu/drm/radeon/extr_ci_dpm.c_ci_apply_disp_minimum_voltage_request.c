#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct TYPE_9__ {scalar_t__ current_dispclk; } ;
struct radeon_clock_voltage_dependency_table {size_t count; TYPE_5__* entries; } ;
struct TYPE_6__ {struct radeon_clock_voltage_dependency_table vddc_dependency_on_sclk; struct radeon_clock_voltage_dependency_table vddc_dependency_on_dispclk; } ;
struct TYPE_7__ {TYPE_1__ dyn_state; } ;
struct TYPE_8__ {TYPE_2__ dpm; } ;
struct radeon_device {TYPE_4__ clock; TYPE_3__ pm; } ;
struct TYPE_10__ {scalar_t__ clk; size_t v; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  PPSMC_MSG_VddC_Request ; 
 scalar_t__ PPSMC_Result_OK ; 
 size_t VOLTAGE_SCALE ; 
 scalar_t__ ci_send_msg_to_smc_with_parameter (struct radeon_device*,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static int ci_apply_disp_minimum_voltage_request(struct radeon_device *rdev)
{
	struct radeon_clock_voltage_dependency_table *disp_voltage_table =
		&rdev->pm.dpm.dyn_state.vddc_dependency_on_dispclk;
	struct radeon_clock_voltage_dependency_table *vddc_table =
		&rdev->pm.dpm.dyn_state.vddc_dependency_on_sclk;
	u32 requested_voltage = 0;
	u32 i;

	if (disp_voltage_table == NULL)
		return -EINVAL;
	if (!disp_voltage_table->count)
		return -EINVAL;

	for (i = 0; i < disp_voltage_table->count; i++) {
		if (rdev->clock.current_dispclk == disp_voltage_table->entries[i].clk)
			requested_voltage = disp_voltage_table->entries[i].v;
	}

	for (i = 0; i < vddc_table->count; i++) {
		if (requested_voltage <= vddc_table->entries[i].v) {
			requested_voltage = vddc_table->entries[i].v;
			return (ci_send_msg_to_smc_with_parameter(rdev,
								  PPSMC_MSG_VddC_Request,
								  requested_voltage * VOLTAGE_SCALE) == PPSMC_Result_OK) ?
				0 : -EINVAL;
		}
	}

	return -EINVAL;
}
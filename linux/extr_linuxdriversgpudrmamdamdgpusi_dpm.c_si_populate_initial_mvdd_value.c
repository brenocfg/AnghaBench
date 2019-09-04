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
struct si_power_info {int /*<<< orphan*/  mvdd_bootup_value; int /*<<< orphan*/  mvdd_voltage_table; } ;
struct rv7xx_power_info {scalar_t__ mvdd_control; } ;
struct amdgpu_device {int dummy; } ;
struct SISLANDS_SMC_VOLTAGE_VALUE {int dummy; } ;

/* Variables and functions */
 struct rv7xx_power_info* rv770_get_pi (struct amdgpu_device*) ; 
 struct si_power_info* si_get_pi (struct amdgpu_device*) ; 
 int si_populate_voltage_value (struct amdgpu_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct SISLANDS_SMC_VOLTAGE_VALUE*) ; 

__attribute__((used)) static int si_populate_initial_mvdd_value(struct amdgpu_device *adev,
					  struct SISLANDS_SMC_VOLTAGE_VALUE *voltage)
{
	struct rv7xx_power_info *pi = rv770_get_pi(adev);
	struct si_power_info *si_pi = si_get_pi(adev);

	if (pi->mvdd_control)
		return si_populate_voltage_value(adev, &si_pi->mvdd_voltage_table,
						 si_pi->mvdd_bootup_value, voltage);

	return 0;
}
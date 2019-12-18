#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct rv7xx_power_info {scalar_t__ mvdd_split_frequency; int /*<<< orphan*/  mvdd_control; } ;
struct radeon_device {int dummy; } ;
struct evergreen_power_info {int /*<<< orphan*/  mvdd_high_index; int /*<<< orphan*/  mvdd_low_index; } ;
struct TYPE_3__ {void* value; int /*<<< orphan*/  index; } ;
typedef  TYPE_1__ RV770_SMC_VOLTAGE_VALUE ;

/* Variables and functions */
 int /*<<< orphan*/  MVDD_HIGH_VALUE ; 
 int /*<<< orphan*/  MVDD_LOW_VALUE ; 
 void* cpu_to_be16 (int /*<<< orphan*/ ) ; 
 struct evergreen_power_info* evergreen_get_pi (struct radeon_device*) ; 
 struct rv7xx_power_info* rv770_get_pi (struct radeon_device*) ; 

__attribute__((used)) static int cypress_populate_mvdd_value(struct radeon_device *rdev,
				       u32 mclk,
				       RV770_SMC_VOLTAGE_VALUE *voltage)
{
	struct rv7xx_power_info *pi = rv770_get_pi(rdev);
	struct evergreen_power_info *eg_pi = evergreen_get_pi(rdev);

	if (!pi->mvdd_control) {
		voltage->index = eg_pi->mvdd_high_index;
		voltage->value = cpu_to_be16(MVDD_HIGH_VALUE);
		return 0;
	}

	if (mclk <= pi->mvdd_split_frequency) {
		voltage->index = eg_pi->mvdd_low_index;
		voltage->value = cpu_to_be16(MVDD_LOW_VALUE);
	} else {
		voltage->index = eg_pi->mvdd_high_index;
		voltage->value = cpu_to_be16(MVDD_HIGH_VALUE);
	}

	return 0;
}
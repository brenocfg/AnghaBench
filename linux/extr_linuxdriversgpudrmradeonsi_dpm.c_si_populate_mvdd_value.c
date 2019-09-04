#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
typedef  scalar_t__ u32 ;
struct TYPE_6__ {TYPE_1__* entries; scalar_t__ count; } ;
struct si_power_info {TYPE_2__ mvdd_voltage_table; } ;
struct rv7xx_power_info {scalar_t__ mvdd_split_frequency; scalar_t__ mvdd_control; } ;
struct radeon_device {int dummy; } ;
struct TYPE_7__ {size_t index; int /*<<< orphan*/  value; } ;
struct TYPE_5__ {int /*<<< orphan*/  value; } ;
typedef  TYPE_3__ SISLANDS_SMC_VOLTAGE_VALUE ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_be16 (int /*<<< orphan*/ ) ; 
 struct rv7xx_power_info* rv770_get_pi (struct radeon_device*) ; 
 struct si_power_info* si_get_pi (struct radeon_device*) ; 

__attribute__((used)) static int si_populate_mvdd_value(struct radeon_device *rdev, u32 mclk,
				  SISLANDS_SMC_VOLTAGE_VALUE *voltage)
{
	struct rv7xx_power_info *pi = rv770_get_pi(rdev);
	struct si_power_info *si_pi = si_get_pi(rdev);

	if (pi->mvdd_control) {
		if (mclk <= pi->mvdd_split_frequency)
			voltage->index = 0;
		else
			voltage->index = (u8)(si_pi->mvdd_voltage_table.count) - 1;

		voltage->value = cpu_to_be16(si_pi->mvdd_voltage_table.entries[voltage->index].value);
	}
	return 0;
}
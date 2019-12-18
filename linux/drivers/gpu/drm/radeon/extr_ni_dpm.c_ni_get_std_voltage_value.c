#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_11__ {scalar_t__ count; TYPE_1__* entries; } ;
struct TYPE_10__ {TYPE_4__ cac_leakage_table; } ;
struct TYPE_12__ {TYPE_3__ dyn_state; } ;
struct TYPE_9__ {TYPE_5__ dpm; } ;
struct radeon_device {TYPE_2__ pm; } ;
struct TYPE_13__ {size_t index; int /*<<< orphan*/  value; } ;
struct TYPE_8__ {int /*<<< orphan*/  vddc; } ;
typedef  TYPE_6__ NISLANDS_SMC_VOLTAGE_VALUE ;

/* Variables and functions */
 int /*<<< orphan*/  be16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ni_get_std_voltage_value(struct radeon_device *rdev,
				    NISLANDS_SMC_VOLTAGE_VALUE *voltage,
				    u16 *std_voltage)
{
	if (rdev->pm.dpm.dyn_state.cac_leakage_table.entries &&
	    ((u32)voltage->index < rdev->pm.dpm.dyn_state.cac_leakage_table.count))
		*std_voltage = rdev->pm.dpm.dyn_state.cac_leakage_table.entries[voltage->index].vddc;
	else
		*std_voltage = be16_to_cpu(voltage->value);

	return 0;
}
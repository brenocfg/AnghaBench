#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
typedef  scalar_t__ u32 ;
struct amdgpu_vce_clock_voltage_dependency_table {size_t count; TYPE_4__* entries; } ;
struct TYPE_5__ {struct amdgpu_vce_clock_voltage_dependency_table vce_clock_voltage_dependency_table; } ;
struct TYPE_6__ {TYPE_1__ dyn_state; } ;
struct TYPE_7__ {TYPE_2__ dpm; } ;
struct amdgpu_device {TYPE_3__ pm; } ;
struct TYPE_8__ {scalar_t__ evclk; } ;

/* Variables and functions */

__attribute__((used)) static u8 ci_get_vce_boot_level(struct amdgpu_device *adev)
{
	u8 i;
	u32 min_evclk = 30000; /* ??? */
	struct amdgpu_vce_clock_voltage_dependency_table *table =
		&adev->pm.dpm.dyn_state.vce_clock_voltage_dependency_table;

	for (i = 0; i < table->count; i++) {
		if (table->entries[i].evclk >= min_evclk)
			return i;
	}

	return table->count - 1;
}
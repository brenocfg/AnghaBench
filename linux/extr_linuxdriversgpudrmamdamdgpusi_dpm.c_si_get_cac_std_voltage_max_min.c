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
typedef  int u16 ;
struct si_power_info {TYPE_5__* powertune_data; } ;
struct amdgpu_cac_leakage_table {size_t count; TYPE_4__* entries; } ;
struct TYPE_6__ {struct amdgpu_cac_leakage_table cac_leakage_table; } ;
struct TYPE_7__ {TYPE_1__ dyn_state; } ;
struct TYPE_8__ {TYPE_2__ dpm; } ;
struct amdgpu_device {TYPE_3__ pm; } ;
struct TYPE_10__ {int lkge_lut_v0_percent; } ;
struct TYPE_9__ {int vddc; } ;

/* Variables and functions */
 int EINVAL ; 
 struct si_power_info* si_get_pi (struct amdgpu_device*) ; 

__attribute__((used)) static int si_get_cac_std_voltage_max_min(struct amdgpu_device *adev,
					  u16 *max, u16 *min)
{
	struct si_power_info *si_pi = si_get_pi(adev);
	struct amdgpu_cac_leakage_table *table =
		&adev->pm.dpm.dyn_state.cac_leakage_table;
	u32 i;
	u32 v0_loadline;

	if (table == NULL)
		return -EINVAL;

	*max = 0;
	*min = 0xFFFF;

	for (i = 0; i < table->count; i++) {
		if (table->entries[i].vddc > *max)
			*max = table->entries[i].vddc;
		if (table->entries[i].vddc < *min)
			*min = table->entries[i].vddc;
	}

	if (si_pi->powertune_data->lkge_lut_v0_percent > 100)
		return -EINVAL;

	v0_loadline = (*min) * (100 - si_pi->powertune_data->lkge_lut_v0_percent) / 100;

	if (v0_loadline > 0xFFFFUL)
		return -EINVAL;

	*min = (u16)v0_loadline;

	if ((*min > *max) || (*max == 0) || (*min == 0))
		return -EINVAL;

	return 0;
}
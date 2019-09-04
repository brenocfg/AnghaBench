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
typedef  size_t u32 ;
struct ci_single_dpm_table {size_t count; TYPE_1__* dpm_levels; } ;
struct amdgpu_device {int dummy; } ;
struct TYPE_2__ {size_t value; int enabled; } ;

/* Variables and functions */

__attribute__((used)) static void ci_trim_single_dpm_states(struct amdgpu_device *adev,
				      struct ci_single_dpm_table *dpm_table,
				      u32 low_limit, u32 high_limit)
{
	u32 i;

	for (i = 0; i < dpm_table->count; i++) {
		if ((dpm_table->dpm_levels[i].value < low_limit) ||
		    (dpm_table->dpm_levels[i].value > high_limit))
			dpm_table->dpm_levels[i].enabled = false;
		else
			dpm_table->dpm_levels[i].enabled = true;
	}
}
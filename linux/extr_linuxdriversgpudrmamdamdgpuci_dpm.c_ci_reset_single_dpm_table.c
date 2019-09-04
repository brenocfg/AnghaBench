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
struct TYPE_2__ {int enabled; } ;

/* Variables and functions */
 size_t MAX_REGULAR_DPM_NUMBER ; 

__attribute__((used)) static void ci_reset_single_dpm_table(struct amdgpu_device *adev,
				      struct ci_single_dpm_table* dpm_table,
				      u32 count)
{
	u32 i;

	dpm_table->count = count;
	for (i = 0; i < MAX_REGULAR_DPM_NUMBER; i++)
		dpm_table->dpm_levels[i].enabled = false;
}
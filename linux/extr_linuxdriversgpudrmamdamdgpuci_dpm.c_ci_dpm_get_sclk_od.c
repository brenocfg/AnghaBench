#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ci_single_dpm_table {int count; TYPE_3__* dpm_levels; } ;
struct TYPE_5__ {struct ci_single_dpm_table sclk_table; } ;
struct TYPE_4__ {struct ci_single_dpm_table sclk_table; } ;
struct ci_power_info {TYPE_2__ golden_dpm_table; TYPE_1__ dpm_table; } ;
struct amdgpu_device {int dummy; } ;
struct TYPE_6__ {int value; } ;

/* Variables and functions */
 struct ci_power_info* ci_get_pi (struct amdgpu_device*) ; 

__attribute__((used)) static int ci_dpm_get_sclk_od(void *handle)
{
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;
	struct ci_power_info *pi = ci_get_pi(adev);
	struct ci_single_dpm_table *sclk_table = &(pi->dpm_table.sclk_table);
	struct ci_single_dpm_table *golden_sclk_table =
			&(pi->golden_dpm_table.sclk_table);
	int value;

	value = (sclk_table->dpm_levels[sclk_table->count - 1].value -
			golden_sclk_table->dpm_levels[golden_sclk_table->count - 1].value) *
			100 /
			golden_sclk_table->dpm_levels[golden_sclk_table->count - 1].value;

	return value;
}
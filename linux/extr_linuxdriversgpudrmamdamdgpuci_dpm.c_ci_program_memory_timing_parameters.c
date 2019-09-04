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
struct ci_power_info {scalar_t__ need_update_smu7_dpm_table; } ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int ci_do_program_memory_timing_parameters (struct amdgpu_device*) ; 
 struct ci_power_info* ci_get_pi (struct amdgpu_device*) ; 

__attribute__((used)) static int ci_program_memory_timing_parameters(struct amdgpu_device *adev)
{
	struct ci_power_info *pi = ci_get_pi(adev);

	if (pi->need_update_smu7_dpm_table == 0)
		return 0;

	return ci_do_program_memory_timing_parameters(adev);
}
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
struct amdgpu_ps {int dummy; } ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SISLANDS_DRIVER_STATE_ARB_INDEX ; 
 int si_do_program_memory_timing_parameters (struct amdgpu_device*,struct amdgpu_ps*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int si_program_memory_timing_parameters(struct amdgpu_device *adev,
					       struct amdgpu_ps *amdgpu_new_state)
{
	return si_do_program_memory_timing_parameters(adev, amdgpu_new_state,
						      SISLANDS_DRIVER_STATE_ARB_INDEX);
}
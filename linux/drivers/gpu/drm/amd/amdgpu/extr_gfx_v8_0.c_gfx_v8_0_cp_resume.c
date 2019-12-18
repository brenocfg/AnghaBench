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
struct amdgpu_device {int flags; } ;

/* Variables and functions */
 int AMD_IS_APU ; 
 int gfx_v8_0_cp_gfx_resume (struct amdgpu_device*) ; 
 int gfx_v8_0_cp_test_all_rings (struct amdgpu_device*) ; 
 int /*<<< orphan*/  gfx_v8_0_enable_gui_idle_interrupt (struct amdgpu_device*,int) ; 
 int gfx_v8_0_kcq_resume (struct amdgpu_device*) ; 
 int gfx_v8_0_kiq_resume (struct amdgpu_device*) ; 

__attribute__((used)) static int gfx_v8_0_cp_resume(struct amdgpu_device *adev)
{
	int r;

	if (!(adev->flags & AMD_IS_APU))
		gfx_v8_0_enable_gui_idle_interrupt(adev, false);

	r = gfx_v8_0_kiq_resume(adev);
	if (r)
		return r;

	r = gfx_v8_0_cp_gfx_resume(adev);
	if (r)
		return r;

	r = gfx_v8_0_kcq_resume(adev);
	if (r)
		return r;

	r = gfx_v8_0_cp_test_all_rings(adev);
	if (r)
		return r;

	gfx_v8_0_enable_gui_idle_interrupt(adev, true);

	return 0;
}
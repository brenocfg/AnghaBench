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
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int gfx_v6_0_cp_compute_resume (struct amdgpu_device*) ; 
 int gfx_v6_0_cp_gfx_resume (struct amdgpu_device*) ; 
 int gfx_v6_0_cp_load_microcode (struct amdgpu_device*) ; 
 int /*<<< orphan*/  gfx_v6_0_enable_gui_idle_interrupt (struct amdgpu_device*,int) ; 

__attribute__((used)) static int gfx_v6_0_cp_resume(struct amdgpu_device *adev)
{
	int r;

	gfx_v6_0_enable_gui_idle_interrupt(adev, false);

	r = gfx_v6_0_cp_load_microcode(adev);
	if (r)
		return r;

	r = gfx_v6_0_cp_gfx_resume(adev);
	if (r)
		return r;
	r = gfx_v6_0_cp_compute_resume(adev);
	if (r)
		return r;

	gfx_v6_0_enable_gui_idle_interrupt(adev, true);

	return 0;
}
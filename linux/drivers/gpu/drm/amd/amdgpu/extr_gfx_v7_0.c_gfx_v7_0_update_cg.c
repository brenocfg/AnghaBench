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
 int /*<<< orphan*/  gfx_v7_0_enable_cgcg (struct amdgpu_device*,int) ; 
 int /*<<< orphan*/  gfx_v7_0_enable_gui_idle_interrupt (struct amdgpu_device*,int) ; 
 int /*<<< orphan*/  gfx_v7_0_enable_mgcg (struct amdgpu_device*,int) ; 

__attribute__((used)) static void gfx_v7_0_update_cg(struct amdgpu_device *adev,
			       bool enable)
{
	gfx_v7_0_enable_gui_idle_interrupt(adev, false);
	/* order matters! */
	if (enable) {
		gfx_v7_0_enable_mgcg(adev, true);
		gfx_v7_0_enable_cgcg(adev, true);
	} else {
		gfx_v7_0_enable_cgcg(adev, false);
		gfx_v7_0_enable_mgcg(adev, false);
	}
	gfx_v7_0_enable_gui_idle_interrupt(adev, true);
}
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
typedef  scalar_t__ u32 ;
struct TYPE_2__ {scalar_t__ vram_type; } ;
struct amdgpu_device {TYPE_1__ gmc; } ;

/* Variables and functions */
 scalar_t__ AMDGPU_VRAM_TYPE_GDDR5 ; 
 scalar_t__ amdgpu_dpm_get_vblank_time (struct amdgpu_device*) ; 
 int amdgpu_dpm_get_vrefresh (struct amdgpu_device*) ; 

__attribute__((used)) static bool ci_dpm_vblank_too_short(void *handle)
{
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;
	u32 vblank_time = amdgpu_dpm_get_vblank_time(adev);
	u32 switch_limit = adev->gmc.vram_type == AMDGPU_VRAM_TYPE_GDDR5 ? 450 : 300;

	/* disable mclk switching if the refresh is >120Hz, even if the
	 * blanking period would allow it
	 */
	if (amdgpu_dpm_get_vrefresh(adev) > 120)
		return true;

	if (vblank_time < switch_limit)
		return true;
	else
		return false;

}
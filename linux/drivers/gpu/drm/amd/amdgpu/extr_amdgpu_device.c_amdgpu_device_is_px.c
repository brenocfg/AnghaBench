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
struct drm_device {struct amdgpu_device* dev_private; } ;
struct amdgpu_device {int flags; } ;

/* Variables and functions */
 int AMD_IS_PX ; 

bool amdgpu_device_is_px(struct drm_device *dev)
{
	struct amdgpu_device *adev = dev->dev_private;

	if (adev->flags & AMD_IS_PX)
		return true;
	return false;
}
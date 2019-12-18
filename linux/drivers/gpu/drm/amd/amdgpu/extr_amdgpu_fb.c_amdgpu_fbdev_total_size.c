#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_3__* rfbdev; } ;
struct amdgpu_device {TYPE_4__ mode_info; } ;
struct amdgpu_bo {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/ * obj; } ;
struct TYPE_6__ {TYPE_1__ base; } ;
struct TYPE_7__ {TYPE_2__ rfb; } ;

/* Variables and functions */
 scalar_t__ amdgpu_bo_size (struct amdgpu_bo*) ; 
 struct amdgpu_bo* gem_to_amdgpu_bo (int /*<<< orphan*/ ) ; 

int amdgpu_fbdev_total_size(struct amdgpu_device *adev)
{
	struct amdgpu_bo *robj;
	int size = 0;

	if (!adev->mode_info.rfbdev)
		return 0;

	robj = gem_to_amdgpu_bo(adev->mode_info.rfbdev->rfb.base.obj[0]);
	size += amdgpu_bo_size(robj);
	return size;
}
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
struct amdgpu_device {int num_ip_blocks; TYPE_3__* ip_blocks; } ;
struct TYPE_8__ {scalar_t__ hang; int /*<<< orphan*/  valid; } ;
struct TYPE_7__ {TYPE_2__* version; TYPE_4__ status; } ;
struct TYPE_6__ {TYPE_1__* funcs; } ;
struct TYPE_5__ {int (* post_soft_reset ) (struct amdgpu_device*) ;} ;

/* Variables and functions */
 int stub1 (struct amdgpu_device*) ; 

__attribute__((used)) static int amdgpu_device_ip_post_soft_reset(struct amdgpu_device *adev)
{
	int i, r = 0;

	for (i = 0; i < adev->num_ip_blocks; i++) {
		if (!adev->ip_blocks[i].status.valid)
			continue;
		if (adev->ip_blocks[i].status.hang &&
		    adev->ip_blocks[i].version->funcs->post_soft_reset)
			r = adev->ip_blocks[i].version->funcs->post_soft_reset(adev);
		if (r)
			return r;
	}

	return 0;
}
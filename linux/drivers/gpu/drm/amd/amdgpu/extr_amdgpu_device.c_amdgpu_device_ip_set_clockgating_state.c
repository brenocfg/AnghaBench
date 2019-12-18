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
struct amdgpu_device {int num_ip_blocks; TYPE_4__* ip_blocks; } ;
typedef  enum amd_ip_block_type { ____Placeholder_amd_ip_block_type } amd_ip_block_type ;
typedef  enum amd_clockgating_state { ____Placeholder_amd_clockgating_state } amd_clockgating_state ;
struct TYPE_5__ {int /*<<< orphan*/  valid; } ;
struct TYPE_8__ {TYPE_3__* version; TYPE_1__ status; } ;
struct TYPE_7__ {int type; TYPE_2__* funcs; } ;
struct TYPE_6__ {int (* set_clockgating_state ) (void*,int) ;int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int /*<<< orphan*/ ,int) ; 
 int stub1 (void*,int) ; 

int amdgpu_device_ip_set_clockgating_state(void *dev,
					   enum amd_ip_block_type block_type,
					   enum amd_clockgating_state state)
{
	struct amdgpu_device *adev = dev;
	int i, r = 0;

	for (i = 0; i < adev->num_ip_blocks; i++) {
		if (!adev->ip_blocks[i].status.valid)
			continue;
		if (adev->ip_blocks[i].version->type != block_type)
			continue;
		if (!adev->ip_blocks[i].version->funcs->set_clockgating_state)
			continue;
		r = adev->ip_blocks[i].version->funcs->set_clockgating_state(
			(void *)adev, state);
		if (r)
			DRM_ERROR("set_clockgating_state of IP block <%s> failed %d\n",
				  adev->ip_blocks[i].version->funcs->name, r);
	}
	return r;
}
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
typedef  enum amd_ip_block_type { ____Placeholder_amd_ip_block_type } amd_ip_block_type ;
struct TYPE_8__ {int (* is_idle ) (void*) ;} ;
struct TYPE_5__ {int /*<<< orphan*/  valid; } ;
struct TYPE_7__ {TYPE_2__* version; TYPE_1__ status; } ;
struct TYPE_6__ {int type; TYPE_4__* funcs; } ;

/* Variables and functions */
 int stub1 (void*) ; 

bool amdgpu_device_ip_is_idle(struct amdgpu_device *adev,
			      enum amd_ip_block_type block_type)
{
	int i;

	for (i = 0; i < adev->num_ip_blocks; i++) {
		if (!adev->ip_blocks[i].status.valid)
			continue;
		if (adev->ip_blocks[i].version->type == block_type)
			return adev->ip_blocks[i].version->funcs->is_idle((void *)adev);
	}
	return true;

}
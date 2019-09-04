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
typedef  int /*<<< orphan*/  u32 ;
struct amdgpu_device {int num_ip_blocks; TYPE_4__* ip_blocks; } ;
struct TYPE_5__ {int /*<<< orphan*/  valid; } ;
struct TYPE_8__ {TYPE_3__* version; TYPE_1__ status; } ;
struct TYPE_7__ {TYPE_2__* funcs; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* get_clockgating_state ) (void*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (void*,int /*<<< orphan*/ *) ; 

void amdgpu_device_ip_get_clockgating_state(struct amdgpu_device *adev,
					    u32 *flags)
{
	int i;

	for (i = 0; i < adev->num_ip_blocks; i++) {
		if (!adev->ip_blocks[i].status.valid)
			continue;
		if (adev->ip_blocks[i].version->funcs->get_clockgating_state)
			adev->ip_blocks[i].version->funcs->get_clockgating_state((void *)adev, flags);
	}
}
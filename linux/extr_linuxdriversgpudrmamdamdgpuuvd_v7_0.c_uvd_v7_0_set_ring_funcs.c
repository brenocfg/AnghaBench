#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int num_uvd_inst; int harvest_config; TYPE_3__* inst; } ;
struct amdgpu_device {TYPE_2__ uvd; } ;
struct TYPE_4__ {int me; int /*<<< orphan*/ * funcs; } ;
struct TYPE_6__ {TYPE_1__ ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_INFO (char*,int) ; 
 int /*<<< orphan*/  uvd_v7_0_ring_vm_funcs ; 

__attribute__((used)) static void uvd_v7_0_set_ring_funcs(struct amdgpu_device *adev)
{
	int i;

	for (i = 0; i < adev->uvd.num_uvd_inst; i++) {
		if (adev->uvd.harvest_config & (1 << i))
			continue;
		adev->uvd.inst[i].ring.funcs = &uvd_v7_0_ring_vm_funcs;
		adev->uvd.inst[i].ring.me = i;
		DRM_INFO("UVD(%d) is enabled in VM mode\n", i);
	}
}
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
struct TYPE_6__ {int num_vcn_inst; int harvest_config; TYPE_2__* inst; } ;
struct amdgpu_device {TYPE_3__ vcn; } ;
struct TYPE_4__ {int me; int /*<<< orphan*/ * funcs; } ;
struct TYPE_5__ {TYPE_1__ ring_dec; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_INFO (char*,int) ; 
 int /*<<< orphan*/  vcn_v2_5_dec_ring_vm_funcs ; 

__attribute__((used)) static void vcn_v2_5_set_dec_ring_funcs(struct amdgpu_device *adev)
{
	int i;

	for (i = 0; i < adev->vcn.num_vcn_inst; ++i) {
		if (adev->vcn.harvest_config & (1 << i))
			continue;
		adev->vcn.inst[i].ring_dec.funcs = &vcn_v2_5_dec_ring_vm_funcs;
		adev->vcn.inst[i].ring_dec.me = i;
		DRM_INFO("VCN(%d) decode is enabled in VM mode\n", i);
	}
}
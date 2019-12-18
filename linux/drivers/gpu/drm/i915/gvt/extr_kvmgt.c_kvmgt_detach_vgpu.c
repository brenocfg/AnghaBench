#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int num_regions; TYPE_3__* region; } ;
struct intel_vgpu {TYPE_2__ vdev; } ;
struct TYPE_7__ {TYPE_1__* ops; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* release ) (struct intel_vgpu*,TYPE_3__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (TYPE_3__*) ; 
 int /*<<< orphan*/  stub1 (struct intel_vgpu*,TYPE_3__*) ; 

__attribute__((used)) static void kvmgt_detach_vgpu(void *p_vgpu)
{
	int i;
	struct intel_vgpu *vgpu = (struct intel_vgpu *)p_vgpu;

	if (!vgpu->vdev.region)
		return;

	for (i = 0; i < vgpu->vdev.num_regions; i++)
		if (vgpu->vdev.region[i].ops->release)
			vgpu->vdev.region[i].ops->release(vgpu,
					&vgpu->vdev.region[i]);
	vgpu->vdev.num_regions = 0;
	kfree(vgpu->vdev.region);
	vgpu->vdev.region = NULL;
}
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
struct drm_gpu_scheduler {int /*<<< orphan*/ * sched_rq; } ;
struct TYPE_7__ {unsigned int num_instances; TYPE_2__* instance; } ;
struct TYPE_8__ {unsigned int vm_pte_num_rqs; int /*<<< orphan*/ ** vm_pte_rqs; int /*<<< orphan*/ * vm_pte_funcs; } ;
struct amdgpu_device {TYPE_3__ sdma; TYPE_4__ vm_manager; } ;
struct TYPE_5__ {struct drm_gpu_scheduler sched; } ;
struct TYPE_6__ {TYPE_1__ ring; } ;

/* Variables and functions */
 size_t DRM_SCHED_PRIORITY_KERNEL ; 
 int /*<<< orphan*/  sdma_v5_0_vm_pte_funcs ; 

__attribute__((used)) static void sdma_v5_0_set_vm_pte_funcs(struct amdgpu_device *adev)
{
	struct drm_gpu_scheduler *sched;
	unsigned i;

	if (adev->vm_manager.vm_pte_funcs == NULL) {
		adev->vm_manager.vm_pte_funcs = &sdma_v5_0_vm_pte_funcs;
		for (i = 0; i < adev->sdma.num_instances; i++) {
			sched = &adev->sdma.instance[i].ring.sched;
			adev->vm_manager.vm_pte_rqs[i] =
				&sched->sched_rq[DRM_SCHED_PRIORITY_KERNEL];
		}
		adev->vm_manager.vm_pte_num_rqs = adev->sdma.num_instances;
	}
}
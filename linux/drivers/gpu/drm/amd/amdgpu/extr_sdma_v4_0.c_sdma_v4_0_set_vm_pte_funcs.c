#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct drm_gpu_scheduler {int /*<<< orphan*/ * sched_rq; } ;
struct TYPE_10__ {unsigned int num_instances; TYPE_3__* instance; scalar_t__ has_page_queue; } ;
struct TYPE_9__ {unsigned int vm_pte_num_rqs; int /*<<< orphan*/ ** vm_pte_rqs; int /*<<< orphan*/ * vm_pte_funcs; } ;
struct amdgpu_device {TYPE_5__ sdma; TYPE_4__ vm_manager; } ;
struct TYPE_7__ {struct drm_gpu_scheduler sched; } ;
struct TYPE_6__ {struct drm_gpu_scheduler sched; } ;
struct TYPE_8__ {TYPE_2__ ring; TYPE_1__ page; } ;

/* Variables and functions */
 size_t DRM_SCHED_PRIORITY_KERNEL ; 
 int /*<<< orphan*/  sdma_v4_0_vm_pte_funcs ; 

__attribute__((used)) static void sdma_v4_0_set_vm_pte_funcs(struct amdgpu_device *adev)
{
	struct drm_gpu_scheduler *sched;
	unsigned i;

	adev->vm_manager.vm_pte_funcs = &sdma_v4_0_vm_pte_funcs;
	for (i = 0; i < adev->sdma.num_instances; i++) {
		if (adev->sdma.has_page_queue)
			sched = &adev->sdma.instance[i].page.sched;
		else
			sched = &adev->sdma.instance[i].ring.sched;
		adev->vm_manager.vm_pte_rqs[i] =
			&sched->sched_rq[DRM_SCHED_PRIORITY_KERNEL];
	}
	adev->vm_manager.vm_pte_num_rqs = adev->sdma.num_instances;
}
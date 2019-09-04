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
struct TYPE_6__ {unsigned int num_instances; TYPE_1__* instance; } ;
struct TYPE_5__ {unsigned int vm_pte_num_rings; int /*<<< orphan*/ ** vm_pte_rings; int /*<<< orphan*/ * vm_pte_funcs; } ;
struct amdgpu_device {TYPE_3__ sdma; TYPE_2__ vm_manager; } ;
struct TYPE_4__ {int /*<<< orphan*/  ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  si_dma_vm_pte_funcs ; 

__attribute__((used)) static void si_dma_set_vm_pte_funcs(struct amdgpu_device *adev)
{
	unsigned i;

	if (adev->vm_manager.vm_pte_funcs == NULL) {
		adev->vm_manager.vm_pte_funcs = &si_dma_vm_pte_funcs;
		for (i = 0; i < adev->sdma.num_instances; i++)
			adev->vm_manager.vm_pte_rings[i] =
				&adev->sdma.instance[i].ring;

		adev->vm_manager.vm_pte_num_rings = adev->sdma.num_instances;
	}
}
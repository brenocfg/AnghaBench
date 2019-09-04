#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int num_instances; } ;
struct amdgpu_device {TYPE_1__ sdma; } ;

/* Variables and functions */
 int /*<<< orphan*/  si_dma_set_buffer_funcs (struct amdgpu_device*) ; 
 int /*<<< orphan*/  si_dma_set_irq_funcs (struct amdgpu_device*) ; 
 int /*<<< orphan*/  si_dma_set_ring_funcs (struct amdgpu_device*) ; 
 int /*<<< orphan*/  si_dma_set_vm_pte_funcs (struct amdgpu_device*) ; 

__attribute__((used)) static int si_dma_early_init(void *handle)
{
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;

	adev->sdma.num_instances = 2;

	si_dma_set_ring_funcs(adev);
	si_dma_set_buffer_funcs(adev);
	si_dma_set_vm_pte_funcs(adev);
	si_dma_set_irq_funcs(adev);

	return 0;
}
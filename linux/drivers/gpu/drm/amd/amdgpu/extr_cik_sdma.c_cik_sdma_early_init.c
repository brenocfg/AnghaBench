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
struct TYPE_2__ {int /*<<< orphan*/  num_instances; } ;
struct amdgpu_device {TYPE_1__ sdma; } ;

/* Variables and functions */
 int /*<<< orphan*/  SDMA_MAX_INSTANCE ; 
 int /*<<< orphan*/  cik_sdma_set_buffer_funcs (struct amdgpu_device*) ; 
 int /*<<< orphan*/  cik_sdma_set_irq_funcs (struct amdgpu_device*) ; 
 int /*<<< orphan*/  cik_sdma_set_ring_funcs (struct amdgpu_device*) ; 
 int /*<<< orphan*/  cik_sdma_set_vm_pte_funcs (struct amdgpu_device*) ; 

__attribute__((used)) static int cik_sdma_early_init(void *handle)
{
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;

	adev->sdma.num_instances = SDMA_MAX_INSTANCE;

	cik_sdma_set_ring_funcs(adev);
	cik_sdma_set_irq_funcs(adev);
	cik_sdma_set_buffer_funcs(adev);
	cik_sdma_set_vm_pte_funcs(adev);

	return 0;
}
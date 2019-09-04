#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int uint32_t ;
struct amdgpu_vm {int pd_phys_addr; } ;

/* Variables and functions */
 int AMDGPU_GPU_PAGE_SHIFT ; 

uint32_t amdgpu_amdkfd_gpuvm_get_process_page_dir(void *vm)
{
	struct amdgpu_vm *avm = (struct amdgpu_vm *)vm;

	return avm->pd_phys_addr >> AMDGPU_GPU_PAGE_SHIFT;
}
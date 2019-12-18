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
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ uint32_t ;
struct amdgpu_vm_update_params {int /*<<< orphan*/  adev; scalar_t__ pages_addr; } ;
struct amdgpu_bo {int dummy; } ;

/* Variables and functions */
 scalar_t__ amdgpu_bo_kptr (struct amdgpu_bo*) ; 
 int /*<<< orphan*/  amdgpu_gmc_set_pte_pde (int /*<<< orphan*/ ,void*,unsigned int,scalar_t__,scalar_t__) ; 
 scalar_t__ amdgpu_vm_map_gart (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  trace_amdgpu_vm_set_ptes (scalar_t__,scalar_t__,unsigned int,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int amdgpu_vm_cpu_update(struct amdgpu_vm_update_params *p,
				struct amdgpu_bo *bo, uint64_t pe,
				uint64_t addr, unsigned count, uint32_t incr,
				uint64_t flags)
{
	unsigned int i;
	uint64_t value;

	pe += (unsigned long)amdgpu_bo_kptr(bo);

	trace_amdgpu_vm_set_ptes(pe, addr, count, incr, flags);

	for (i = 0; i < count; i++) {
		value = p->pages_addr ?
			amdgpu_vm_map_gart(p->pages_addr, addr) :
			addr;
		amdgpu_gmc_set_pte_pde(p->adev, (void *)(uintptr_t)pe,
				       i, value, flags);
		addr += incr;
	}
	return 0;
}
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
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct amdgpu_vm_update_params {TYPE_2__* vm; TYPE_3__* adev; } ;
struct amdgpu_bo {int dummy; } ;
struct TYPE_6__ {scalar_t__ asic_type; } ;
struct TYPE_5__ {TYPE_1__* update_funcs; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* update ) (struct amdgpu_vm_update_params*,struct amdgpu_bo*,int,int,unsigned int,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int AMDGPU_PDE_PTE ; 
 int AMDGPU_PTE_EXECUTABLE ; 
 int AMDGPU_PTE_PRT ; 
 int AMDGPU_PTE_VALID ; 
 unsigned int AMDGPU_VM_PTB ; 
 scalar_t__ CHIP_VEGA10 ; 
 int /*<<< orphan*/  amdgpu_gmc_get_vm_pde (TYPE_3__*,unsigned int,int*,int*) ; 
 int /*<<< orphan*/  stub1 (struct amdgpu_vm_update_params*,struct amdgpu_bo*,int,int,unsigned int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void amdgpu_vm_update_flags(struct amdgpu_vm_update_params *params,
				   struct amdgpu_bo *bo, unsigned level,
				   uint64_t pe, uint64_t addr,
				   unsigned count, uint32_t incr,
				   uint64_t flags)

{
	if (level != AMDGPU_VM_PTB) {
		flags |= AMDGPU_PDE_PTE;
		amdgpu_gmc_get_vm_pde(params->adev, level, &addr, &flags);

	} else if (params->adev->asic_type >= CHIP_VEGA10 &&
		   !(flags & AMDGPU_PTE_VALID) &&
		   !(flags & AMDGPU_PTE_PRT)) {

		/* Workaround for fault priority problem on GMC9 */
		flags |= AMDGPU_PTE_EXECUTABLE;
	}

	params->vm->update_funcs->update(params, bo, pe, addr, count, incr,
					 flags);
}
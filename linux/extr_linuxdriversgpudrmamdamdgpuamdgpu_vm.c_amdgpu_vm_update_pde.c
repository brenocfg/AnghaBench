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
struct TYPE_5__ {struct amdgpu_bo* bo; } ;
struct amdgpu_vm_pt {struct amdgpu_vm_pt* entries; TYPE_2__ base; scalar_t__ huge; } ;
struct amdgpu_vm {int dummy; } ;
struct amdgpu_pte_update_params {int /*<<< orphan*/  (* func ) (struct amdgpu_pte_update_params*,struct amdgpu_bo*,int,int,int,int /*<<< orphan*/ ,int) ;TYPE_3__* adev; } ;
struct amdgpu_bo {struct amdgpu_bo* shadow; struct amdgpu_bo* parent; } ;
struct TYPE_4__ {scalar_t__ root_level; } ;
struct TYPE_6__ {TYPE_1__ vm_manager; } ;

/* Variables and functions */
 int AMDGPU_PTE_VALID ; 
 int amdgpu_bo_gpu_offset (struct amdgpu_bo*) ; 
 int /*<<< orphan*/  amdgpu_gmc_get_vm_pde (TYPE_3__*,unsigned int,int*,int*) ; 
 int /*<<< orphan*/  stub1 (struct amdgpu_pte_update_params*,struct amdgpu_bo*,int,int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub2 (struct amdgpu_pte_update_params*,struct amdgpu_bo*,int,int,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void amdgpu_vm_update_pde(struct amdgpu_pte_update_params *params,
				 struct amdgpu_vm *vm,
				 struct amdgpu_vm_pt *parent,
				 struct amdgpu_vm_pt *entry)
{
	struct amdgpu_bo *bo = parent->base.bo, *pbo;
	uint64_t pde, pt, flags;
	unsigned level;

	/* Don't update huge pages here */
	if (entry->huge)
		return;

	for (level = 0, pbo = bo->parent; pbo; ++level)
		pbo = pbo->parent;

	level += params->adev->vm_manager.root_level;
	pt = amdgpu_bo_gpu_offset(entry->base.bo);
	flags = AMDGPU_PTE_VALID;
	amdgpu_gmc_get_vm_pde(params->adev, level, &pt, &flags);
	pde = (entry - parent->entries) * 8;
	if (bo->shadow)
		params->func(params, bo->shadow, pde, pt, 1, 0, flags);
	params->func(params, bo, pde, pt, 1, 0, flags);
}
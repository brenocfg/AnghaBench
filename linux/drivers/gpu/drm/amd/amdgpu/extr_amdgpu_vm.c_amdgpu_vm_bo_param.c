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
struct TYPE_9__ {TYPE_3__* bo; } ;
struct TYPE_10__ {TYPE_4__ base; } ;
struct amdgpu_vm {TYPE_5__ root; scalar_t__ use_cpu_for_update; } ;
struct amdgpu_device {int dummy; } ;
struct amdgpu_bo_param {int flags; int /*<<< orphan*/  resv; int /*<<< orphan*/  type; int /*<<< orphan*/  domain; int /*<<< orphan*/  byte_align; int /*<<< orphan*/  size; } ;
struct TYPE_6__ {int /*<<< orphan*/  resv; } ;
struct TYPE_7__ {TYPE_1__ base; } ;
struct TYPE_8__ {TYPE_2__ tbo; scalar_t__ shadow; } ;

/* Variables and functions */
 int AMDGPU_GEM_CREATE_CPU_ACCESS_REQUIRED ; 
 int AMDGPU_GEM_CREATE_CPU_GTT_USWC ; 
 int AMDGPU_GEM_CREATE_SHADOW ; 
 int AMDGPU_GEM_CREATE_VRAM_CONTIGUOUS ; 
 int /*<<< orphan*/  AMDGPU_GEM_DOMAIN_VRAM ; 
 int /*<<< orphan*/  AMDGPU_GPU_PAGE_SIZE ; 
 int /*<<< orphan*/  amdgpu_bo_get_preferred_pin_domain (struct amdgpu_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_vm_bo_size (struct amdgpu_device*,int) ; 
 int /*<<< orphan*/  memset (struct amdgpu_bo_param*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ttm_bo_type_kernel ; 

__attribute__((used)) static void amdgpu_vm_bo_param(struct amdgpu_device *adev, struct amdgpu_vm *vm,
			       int level, struct amdgpu_bo_param *bp)
{
	memset(bp, 0, sizeof(*bp));

	bp->size = amdgpu_vm_bo_size(adev, level);
	bp->byte_align = AMDGPU_GPU_PAGE_SIZE;
	bp->domain = AMDGPU_GEM_DOMAIN_VRAM;
	bp->domain = amdgpu_bo_get_preferred_pin_domain(adev, bp->domain);
	bp->flags = AMDGPU_GEM_CREATE_VRAM_CONTIGUOUS |
		AMDGPU_GEM_CREATE_CPU_GTT_USWC;
	if (vm->use_cpu_for_update)
		bp->flags |= AMDGPU_GEM_CREATE_CPU_ACCESS_REQUIRED;
	else if (!vm->root.base.bo || vm->root.base.bo->shadow)
		bp->flags |= AMDGPU_GEM_CREATE_SHADOW;
	bp->type = ttm_bo_type_kernel;
	if (vm->root.base.bo)
		bp->resv = vm->root.base.bo->tbo.base.resv;
}
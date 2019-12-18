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
struct ttm_place {int dummy; } ;
struct ttm_mem_type_manager {int dummy; } ;
struct ttm_mem_reg {int num_pages; int start; int /*<<< orphan*/ * mm_node; } ;
struct ttm_buffer_object {int /*<<< orphan*/  bdev; } ;
struct nouveau_mem {TYPE_3__* vma; TYPE_2__* cli; } ;
struct nouveau_drm {int /*<<< orphan*/  master; } ;
struct nouveau_bo {int /*<<< orphan*/  comp; int /*<<< orphan*/  kind; } ;
struct TYPE_6__ {int addr; } ;
struct TYPE_4__ {int /*<<< orphan*/  vmm; } ;
struct TYPE_5__ {TYPE_1__ vmm; } ;

/* Variables and functions */
 int ENOSPC ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  PTES ; 
 struct nouveau_drm* nouveau_bdev (int /*<<< orphan*/ ) ; 
 struct nouveau_bo* nouveau_bo (struct ttm_buffer_object*) ; 
 struct nouveau_mem* nouveau_mem (struct ttm_mem_reg*) ; 
 int /*<<< orphan*/  nouveau_mem_del (struct ttm_mem_reg*) ; 
 int nouveau_mem_new (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ttm_mem_reg*) ; 
 int nvif_vmm_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int,TYPE_3__*) ; 

__attribute__((used)) static int
nv04_gart_manager_new(struct ttm_mem_type_manager *man,
		      struct ttm_buffer_object *bo,
		      const struct ttm_place *place,
		      struct ttm_mem_reg *reg)
{
	struct nouveau_bo *nvbo = nouveau_bo(bo);
	struct nouveau_drm *drm = nouveau_bdev(bo->bdev);
	struct nouveau_mem *mem;
	int ret;

	ret = nouveau_mem_new(&drm->master, nvbo->kind, nvbo->comp, reg);
	mem = nouveau_mem(reg);
	if (ret)
		return ret;

	ret = nvif_vmm_get(&mem->cli->vmm.vmm, PTES, false, 12, 0,
			   reg->num_pages << PAGE_SHIFT, &mem->vma[0]);
	if (ret) {
		nouveau_mem_del(reg);
		if (ret == -ENOSPC) {
			reg->mm_node = NULL;
			return 0;
		}
		return ret;
	}

	reg->start = mem->vma[0].addr >> PAGE_SHIFT;
	return 0;
}
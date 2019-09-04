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
struct ttm_mem_reg {int /*<<< orphan*/ * mm_node; } ;
struct ttm_buffer_object {int /*<<< orphan*/  bdev; } ;
struct nouveau_mem {int dummy; } ;
struct TYPE_4__ {scalar_t__ ram_size; } ;
struct TYPE_5__ {TYPE_1__ info; } ;
struct TYPE_6__ {TYPE_2__ device; } ;
struct nouveau_drm {int /*<<< orphan*/  master; TYPE_3__ client; } ;
struct nouveau_bo {int /*<<< orphan*/  page; int /*<<< orphan*/  contig; int /*<<< orphan*/  comp; int /*<<< orphan*/  kind; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ENOSPC ; 
 struct nouveau_drm* nouveau_bdev (int /*<<< orphan*/ ) ; 
 struct nouveau_bo* nouveau_bo (struct ttm_buffer_object*) ; 
 struct nouveau_mem* nouveau_mem (struct ttm_mem_reg*) ; 
 int /*<<< orphan*/  nouveau_mem_del (struct ttm_mem_reg*) ; 
 int nouveau_mem_new (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ttm_mem_reg*) ; 
 int nouveau_mem_vram (struct ttm_mem_reg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nouveau_vram_manager_new(struct ttm_mem_type_manager *man,
			 struct ttm_buffer_object *bo,
			 const struct ttm_place *place,
			 struct ttm_mem_reg *reg)
{
	struct nouveau_bo *nvbo = nouveau_bo(bo);
	struct nouveau_drm *drm = nouveau_bdev(bo->bdev);
	struct nouveau_mem *mem;
	int ret;

	if (drm->client.device.info.ram_size == 0)
		return -ENOMEM;

	ret = nouveau_mem_new(&drm->master, nvbo->kind, nvbo->comp, reg);
	mem = nouveau_mem(reg);
	if (ret)
		return ret;

	ret = nouveau_mem_vram(reg, nvbo->contig, nvbo->page);
	if (ret) {
		nouveau_mem_del(reg);
		if (ret == -ENOSPC) {
			reg->mm_node = NULL;
			return 0;
		}
		return ret;
	}

	return 0;
}
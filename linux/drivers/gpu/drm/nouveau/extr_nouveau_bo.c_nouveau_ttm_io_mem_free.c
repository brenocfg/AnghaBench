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
struct ttm_mem_reg {int mem_type; } ;
struct ttm_bo_device {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  object; } ;
struct nouveau_mem {TYPE_3__ mem; int /*<<< orphan*/  kind; } ;
struct TYPE_5__ {TYPE_1__* mem; } ;
struct nouveau_drm {TYPE_2__ client; } ;
struct TYPE_4__ {scalar_t__ oclass; } ;

/* Variables and functions */
 scalar_t__ NVIF_CLASS_MEM_NV50 ; 
#define  TTM_PL_TT 129 
#define  TTM_PL_VRAM 128 
 struct nouveau_drm* nouveau_bdev (struct ttm_bo_device*) ; 
 struct nouveau_mem* nouveau_mem (struct ttm_mem_reg*) ; 
 int /*<<< orphan*/  nvif_object_unmap_handle (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
nouveau_ttm_io_mem_free(struct ttm_bo_device *bdev, struct ttm_mem_reg *reg)
{
	struct nouveau_drm *drm = nouveau_bdev(bdev);
	struct nouveau_mem *mem = nouveau_mem(reg);

	if (drm->client.mem->oclass >= NVIF_CLASS_MEM_NV50) {
		switch (reg->mem_type) {
		case TTM_PL_TT:
			if (mem->kind)
				nvif_object_unmap_handle(&mem->mem.object);
			break;
		case TTM_PL_VRAM:
			nvif_object_unmap_handle(&mem->mem.object);
			break;
		default:
			break;
		}
	}
}
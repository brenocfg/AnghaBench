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
struct ttm_bo_kmap_obj {void* virtual; } ;
struct TYPE_2__ {int /*<<< orphan*/  num_pages; } ;
struct drm_gem_vram_object {TYPE_1__ bo; struct ttm_bo_kmap_obj kmap; } ;

/* Variables and functions */
 void* ERR_PTR (int) ; 
 int ttm_bo_kmap (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ttm_bo_kmap_obj*) ; 
 void* ttm_kmap_obj_virtual (struct ttm_bo_kmap_obj*,int*) ; 

void *drm_gem_vram_kmap(struct drm_gem_vram_object *gbo, bool map,
			bool *is_iomem)
{
	int ret;
	struct ttm_bo_kmap_obj *kmap = &gbo->kmap;

	if (kmap->virtual || !map)
		goto out;

	ret = ttm_bo_kmap(&gbo->bo, 0, gbo->bo.num_pages, kmap);
	if (ret)
		return ERR_PTR(ret);

out:
	if (!is_iomem)
		return kmap->virtual;
	if (!kmap->virtual) {
		*is_iomem = false;
		return NULL;
	}
	return ttm_kmap_obj_virtual(kmap, is_iomem);
}
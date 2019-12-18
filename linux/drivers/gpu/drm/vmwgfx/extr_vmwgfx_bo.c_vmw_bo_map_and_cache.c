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
struct ttm_buffer_object {int /*<<< orphan*/  num_pages; } ;
struct vmw_buffer_object {int /*<<< orphan*/  map; struct ttm_buffer_object base; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int ttm_bo_kmap (struct ttm_buffer_object*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* ttm_kmap_obj_virtual (int /*<<< orphan*/ *,int*) ; 

void *vmw_bo_map_and_cache(struct vmw_buffer_object *vbo)
{
	struct ttm_buffer_object *bo = &vbo->base;
	bool not_used;
	void *virtual;
	int ret;

	virtual = ttm_kmap_obj_virtual(&vbo->map, &not_used);
	if (virtual)
		return virtual;

	ret = ttm_bo_kmap(bo, 0, bo->num_pages, &vbo->map);
	if (ret)
		DRM_ERROR("Buffer object map failed: %d.\n", ret);

	return ttm_kmap_obj_virtual(&vbo->map, &not_used);
}
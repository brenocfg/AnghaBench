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
typedef  int u32 ;
struct vmw_private {int dummy; } ;
struct vmw_buffer_object {int /*<<< orphan*/  base; } ;
struct ttm_bo_kmap_obj {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int EINVAL ; 
 int PAGE_SHIFT ; 
 int PAGE_SIZE ; 
 int ttm_bo_kmap (int /*<<< orphan*/ *,unsigned long,unsigned long,struct ttm_bo_kmap_obj*) ; 
 int /*<<< orphan*/  ttm_bo_kunmap (struct ttm_bo_kmap_obj*) ; 
 int ttm_bo_reserve (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ttm_bo_unreserve (int /*<<< orphan*/ *) ; 
 void* ttm_kmap_obj_virtual (struct ttm_bo_kmap_obj*,int*) ; 
 scalar_t__ unlikely (int) ; 
 int vmw_cursor_update_image (struct vmw_private*,void*,int,int,int,int) ; 

__attribute__((used)) static int vmw_cursor_update_bo(struct vmw_private *dev_priv,
				struct vmw_buffer_object *bo,
				u32 width, u32 height,
				u32 hotspotX, u32 hotspotY)
{
	struct ttm_bo_kmap_obj map;
	unsigned long kmap_offset;
	unsigned long kmap_num;
	void *virtual;
	bool dummy;
	int ret;

	kmap_offset = 0;
	kmap_num = (width*height*4 + PAGE_SIZE - 1) >> PAGE_SHIFT;

	ret = ttm_bo_reserve(&bo->base, true, false, NULL);
	if (unlikely(ret != 0)) {
		DRM_ERROR("reserve failed\n");
		return -EINVAL;
	}

	ret = ttm_bo_kmap(&bo->base, kmap_offset, kmap_num, &map);
	if (unlikely(ret != 0))
		goto err_unreserve;

	virtual = ttm_kmap_obj_virtual(&map, &dummy);
	ret = vmw_cursor_update_image(dev_priv, virtual, width, height,
				      hotspotX, hotspotY);

	ttm_bo_kunmap(&map);
err_unreserve:
	ttm_bo_unreserve(&bo->base);

	return ret;
}
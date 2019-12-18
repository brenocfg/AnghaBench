#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vmw_private {struct vmw_buffer_object* dummy_query_bo; } ;
struct vmw_buffer_object {int /*<<< orphan*/  base; } ;
struct ttm_bo_kmap_obj {int dummy; } ;
struct TYPE_3__ {int totalSize; int result32; int /*<<< orphan*/  state; } ;
typedef  TYPE_1__ SVGA3dQueryResult ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  SVGA3D_QUERYSTATE_PENDING ; 
 struct vmw_buffer_object* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 int ttm_bo_kmap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,struct ttm_bo_kmap_obj*) ; 
 int /*<<< orphan*/  ttm_bo_kunmap (struct ttm_bo_kmap_obj*) ; 
 int ttm_bo_reserve (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ttm_bo_unreserve (int /*<<< orphan*/ *) ; 
 TYPE_1__* ttm_kmap_obj_virtual (struct ttm_bo_kmap_obj*,int*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  vmw_bo_bo_free ; 
 int vmw_bo_init (struct vmw_private*,struct vmw_buffer_object*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmw_bo_pin_reserved (struct vmw_buffer_object*,int) ; 
 int /*<<< orphan*/  vmw_bo_unreference (struct vmw_buffer_object**) ; 
 int /*<<< orphan*/  vmw_sys_ne_placement ; 

__attribute__((used)) static int vmw_dummy_query_bo_create(struct vmw_private *dev_priv)
{
	int ret;
	struct vmw_buffer_object *vbo;
	struct ttm_bo_kmap_obj map;
	volatile SVGA3dQueryResult *result;
	bool dummy;

	/*
	 * Create the vbo as pinned, so that a tryreserve will
	 * immediately succeed. This is because we're the only
	 * user of the bo currently.
	 */
	vbo = kzalloc(sizeof(*vbo), GFP_KERNEL);
	if (!vbo)
		return -ENOMEM;

	ret = vmw_bo_init(dev_priv, vbo, PAGE_SIZE,
			  &vmw_sys_ne_placement, false,
			  &vmw_bo_bo_free);
	if (unlikely(ret != 0))
		return ret;

	ret = ttm_bo_reserve(&vbo->base, false, true, NULL);
	BUG_ON(ret != 0);
	vmw_bo_pin_reserved(vbo, true);

	ret = ttm_bo_kmap(&vbo->base, 0, 1, &map);
	if (likely(ret == 0)) {
		result = ttm_kmap_obj_virtual(&map, &dummy);
		result->totalSize = sizeof(*result);
		result->state = SVGA3D_QUERYSTATE_PENDING;
		result->result32 = 0xff;
		ttm_bo_kunmap(&map);
	}
	vmw_bo_pin_reserved(vbo, false);
	ttm_bo_unreserve(&vbo->base);

	if (unlikely(ret != 0)) {
		DRM_ERROR("Dummy query buffer map failed.\n");
		vmw_bo_unreference(&vbo);
	} else
		dev_priv->dummy_query_bo = vbo;

	return ret;
}
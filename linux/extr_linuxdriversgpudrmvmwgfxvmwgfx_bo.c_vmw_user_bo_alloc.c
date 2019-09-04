#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_3__ {int /*<<< orphan*/  key; } ;
struct ttm_base_object {TYPE_1__ hash; int /*<<< orphan*/  refcount; } ;
struct TYPE_4__ {struct ttm_base_object base; } ;
struct vmw_buffer_object {int /*<<< orphan*/  base; } ;
struct vmw_user_buffer_object {TYPE_2__ prime; struct vmw_buffer_object vbo; } ;
struct vmw_private {scalar_t__ has_mob; } ;
struct ttm_object_file {int dummy; } ;
struct ttm_buffer_object {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 struct vmw_user_buffer_object* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct ttm_buffer_object* ttm_bo_reference (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ttm_bo_unref (struct ttm_buffer_object**) ; 
 int /*<<< orphan*/  ttm_buffer_type ; 
 int ttm_prime_object_init (struct ttm_object_file*,int /*<<< orphan*/ ,TYPE_2__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 int vmw_bo_init (struct vmw_private*,struct vmw_buffer_object*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmw_sys_placement ; 
 int /*<<< orphan*/  vmw_user_bo_destroy ; 
 int /*<<< orphan*/  vmw_user_bo_ref_obj_release ; 
 int /*<<< orphan*/  vmw_user_bo_release ; 
 int /*<<< orphan*/  vmw_vram_sys_placement ; 

int vmw_user_bo_alloc(struct vmw_private *dev_priv,
		      struct ttm_object_file *tfile,
		      uint32_t size,
		      bool shareable,
		      uint32_t *handle,
		      struct vmw_buffer_object **p_vbo,
		      struct ttm_base_object **p_base)
{
	struct vmw_user_buffer_object *user_bo;
	struct ttm_buffer_object *tmp;
	int ret;

	user_bo = kzalloc(sizeof(*user_bo), GFP_KERNEL);
	if (unlikely(!user_bo)) {
		DRM_ERROR("Failed to allocate a buffer.\n");
		return -ENOMEM;
	}

	ret = vmw_bo_init(dev_priv, &user_bo->vbo, size,
			  (dev_priv->has_mob) ?
			  &vmw_sys_placement :
			  &vmw_vram_sys_placement, true,
			  &vmw_user_bo_destroy);
	if (unlikely(ret != 0))
		return ret;

	tmp = ttm_bo_reference(&user_bo->vbo.base);
	ret = ttm_prime_object_init(tfile,
				    size,
				    &user_bo->prime,
				    shareable,
				    ttm_buffer_type,
				    &vmw_user_bo_release,
				    &vmw_user_bo_ref_obj_release);
	if (unlikely(ret != 0)) {
		ttm_bo_unref(&tmp);
		goto out_no_base_object;
	}

	*p_vbo = &user_bo->vbo;
	if (p_base) {
		*p_base = &user_bo->prime.base;
		kref_get(&(*p_base)->refcount);
	}
	*handle = user_bo->prime.base.hash.key;

out_no_base_object:
	return ret;
}
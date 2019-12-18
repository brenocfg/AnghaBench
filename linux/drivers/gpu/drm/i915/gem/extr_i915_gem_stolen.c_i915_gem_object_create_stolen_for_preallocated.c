#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct i915_vma {int /*<<< orphan*/  vm_link; int /*<<< orphan*/  flags; int /*<<< orphan*/  pages; int /*<<< orphan*/  node; } ;
struct TYPE_9__ {int /*<<< orphan*/  mutex; int /*<<< orphan*/  bound_list; } ;
struct i915_ggtt {TYPE_4__ vm; } ;
struct drm_mm_node {void* size; void* start; } ;
struct TYPE_7__ {int /*<<< orphan*/  stolen_lock; int /*<<< orphan*/  stolen; } ;
struct TYPE_6__ {int /*<<< orphan*/  struct_mutex; } ;
struct drm_i915_private {TYPE_2__ mm; TYPE_1__ drm; struct i915_ggtt ggtt; } ;
struct TYPE_8__ {int /*<<< orphan*/  pages; } ;
struct drm_i915_gem_object {int /*<<< orphan*/  bind_count; TYPE_3__ mm; int /*<<< orphan*/  cache_level; } ;
typedef  void* resource_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,...) ; 
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I915_GTT_MIN_ALIGNMENT ; 
 void* I915_GTT_OFFSET_NONE ; 
 int /*<<< orphan*/  I915_GTT_PAGE_SIZE ; 
 int /*<<< orphan*/  I915_VMA_GLOBAL_BIND ; 
 int /*<<< orphan*/  IS_ALIGNED (void*,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct i915_vma*) ; 
 int PTR_ERR (struct i915_vma*) ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  __i915_vma_set_map_and_fenceable (struct i915_vma*) ; 
 struct drm_i915_gem_object* _i915_gem_object_create_stolen (struct drm_i915_private*,struct drm_mm_node*) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_mm_initialized (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_mm_node_allocated (int /*<<< orphan*/ *) ; 
 int drm_mm_reserve_node (int /*<<< orphan*/ *,struct drm_mm_node*) ; 
 int i915_gem_gtt_reserve (TYPE_4__*,int /*<<< orphan*/ *,void*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int i915_gem_object_is_shrinkable (struct drm_i915_gem_object*) ; 
 int i915_gem_object_pin_pages (struct drm_i915_gem_object*) ; 
 int /*<<< orphan*/  i915_gem_object_put (struct drm_i915_gem_object*) ; 
 int /*<<< orphan*/  i915_gem_object_unpin_pages (struct drm_i915_gem_object*) ; 
 int /*<<< orphan*/  i915_gem_stolen_remove_node (struct drm_i915_private*,struct drm_mm_node*) ; 
 struct i915_vma* i915_vma_instance (struct drm_i915_gem_object*,TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct drm_mm_node*) ; 
 struct drm_mm_node* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_move_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

struct drm_i915_gem_object *
i915_gem_object_create_stolen_for_preallocated(struct drm_i915_private *dev_priv,
					       resource_size_t stolen_offset,
					       resource_size_t gtt_offset,
					       resource_size_t size)
{
	struct i915_ggtt *ggtt = &dev_priv->ggtt;
	struct drm_i915_gem_object *obj;
	struct drm_mm_node *stolen;
	struct i915_vma *vma;
	int ret;

	if (!drm_mm_initialized(&dev_priv->mm.stolen))
		return NULL;

	lockdep_assert_held(&dev_priv->drm.struct_mutex);

	DRM_DEBUG_DRIVER("creating preallocated stolen object: stolen_offset=%pa, gtt_offset=%pa, size=%pa\n",
			 &stolen_offset, &gtt_offset, &size);

	/* KISS and expect everything to be page-aligned */
	if (WARN_ON(size == 0) ||
	    WARN_ON(!IS_ALIGNED(size, I915_GTT_PAGE_SIZE)) ||
	    WARN_ON(!IS_ALIGNED(stolen_offset, I915_GTT_MIN_ALIGNMENT)))
		return NULL;

	stolen = kzalloc(sizeof(*stolen), GFP_KERNEL);
	if (!stolen)
		return NULL;

	stolen->start = stolen_offset;
	stolen->size = size;
	mutex_lock(&dev_priv->mm.stolen_lock);
	ret = drm_mm_reserve_node(&dev_priv->mm.stolen, stolen);
	mutex_unlock(&dev_priv->mm.stolen_lock);
	if (ret) {
		DRM_DEBUG_DRIVER("failed to allocate stolen space\n");
		kfree(stolen);
		return NULL;
	}

	obj = _i915_gem_object_create_stolen(dev_priv, stolen);
	if (obj == NULL) {
		DRM_DEBUG_DRIVER("failed to allocate stolen object\n");
		i915_gem_stolen_remove_node(dev_priv, stolen);
		kfree(stolen);
		return NULL;
	}

	/* Some objects just need physical mem from stolen space */
	if (gtt_offset == I915_GTT_OFFSET_NONE)
		return obj;

	ret = i915_gem_object_pin_pages(obj);
	if (ret)
		goto err;

	vma = i915_vma_instance(obj, &ggtt->vm, NULL);
	if (IS_ERR(vma)) {
		ret = PTR_ERR(vma);
		goto err_pages;
	}

	/* To simplify the initialisation sequence between KMS and GTT,
	 * we allow construction of the stolen object prior to
	 * setting up the GTT space. The actual reservation will occur
	 * later.
	 */
	ret = i915_gem_gtt_reserve(&ggtt->vm, &vma->node,
				   size, gtt_offset, obj->cache_level,
				   0);
	if (ret) {
		DRM_DEBUG_DRIVER("failed to allocate stolen GTT space\n");
		goto err_pages;
	}

	GEM_BUG_ON(!drm_mm_node_allocated(&vma->node));

	vma->pages = obj->mm.pages;
	vma->flags |= I915_VMA_GLOBAL_BIND;
	__i915_vma_set_map_and_fenceable(vma);

	mutex_lock(&ggtt->vm.mutex);
	list_move_tail(&vma->vm_link, &ggtt->vm.bound_list);
	mutex_unlock(&ggtt->vm.mutex);

	GEM_BUG_ON(i915_gem_object_is_shrinkable(obj));
	atomic_inc(&obj->bind_count);

	return obj;

err_pages:
	i915_gem_object_unpin_pages(obj);
err:
	i915_gem_object_put(obj);
	return NULL;
}
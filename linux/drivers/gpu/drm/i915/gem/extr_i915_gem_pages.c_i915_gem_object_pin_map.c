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
struct TYPE_2__ {int /*<<< orphan*/  pages_pin_count; int /*<<< orphan*/  lock; int /*<<< orphan*/ * mapping; } ;
struct drm_i915_gem_object {TYPE_1__ mm; } ;
typedef  enum i915_map_type { ____Placeholder_i915_map_type } i915_map_type ;

/* Variables and functions */
 int EBUSY ; 
 int ENOMEM ; 
 int ENXIO ; 
 void* ERR_PTR (int) ; 
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int I915_MAP_OVERRIDE ; 
 int ____i915_gem_object_get_pages (struct drm_i915_gem_object*) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc_not_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i915_gem_object_has_pages (struct drm_i915_gem_object*) ; 
 int i915_gem_object_has_pinned_pages (struct drm_i915_gem_object*) ; 
 int /*<<< orphan*/  i915_gem_object_has_struct_page (struct drm_i915_gem_object*) ; 
 void* i915_gem_object_map (struct drm_i915_gem_object*,int) ; 
 scalar_t__ is_vmalloc_addr (void*) ; 
 int /*<<< orphan*/  kmap_to_page (void*) ; 
 int /*<<< orphan*/  kunmap (int /*<<< orphan*/ ) ; 
 int mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * page_pack_bits (void*,int) ; 
 void* page_unpack_bits (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  smp_mb__before_atomic () ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  vunmap (void*) ; 

void *i915_gem_object_pin_map(struct drm_i915_gem_object *obj,
			      enum i915_map_type type)
{
	enum i915_map_type has_type;
	bool pinned;
	void *ptr;
	int err;

	if (unlikely(!i915_gem_object_has_struct_page(obj)))
		return ERR_PTR(-ENXIO);

	err = mutex_lock_interruptible(&obj->mm.lock);
	if (err)
		return ERR_PTR(err);

	pinned = !(type & I915_MAP_OVERRIDE);
	type &= ~I915_MAP_OVERRIDE;

	if (!atomic_inc_not_zero(&obj->mm.pages_pin_count)) {
		if (unlikely(!i915_gem_object_has_pages(obj))) {
			GEM_BUG_ON(i915_gem_object_has_pinned_pages(obj));

			err = ____i915_gem_object_get_pages(obj);
			if (err)
				goto err_unlock;

			smp_mb__before_atomic();
		}
		atomic_inc(&obj->mm.pages_pin_count);
		pinned = false;
	}
	GEM_BUG_ON(!i915_gem_object_has_pages(obj));

	ptr = page_unpack_bits(obj->mm.mapping, &has_type);
	if (ptr && has_type != type) {
		if (pinned) {
			err = -EBUSY;
			goto err_unpin;
		}

		if (is_vmalloc_addr(ptr))
			vunmap(ptr);
		else
			kunmap(kmap_to_page(ptr));

		ptr = obj->mm.mapping = NULL;
	}

	if (!ptr) {
		ptr = i915_gem_object_map(obj, type);
		if (!ptr) {
			err = -ENOMEM;
			goto err_unpin;
		}

		obj->mm.mapping = page_pack_bits(ptr, type);
	}

out_unlock:
	mutex_unlock(&obj->mm.lock);
	return ptr;

err_unpin:
	atomic_dec(&obj->mm.pages_pin_count);
err_unlock:
	ptr = ERR_PTR(err);
	goto out_unlock;
}
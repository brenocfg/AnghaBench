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
struct drm_i915_gem_object {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int
__i915_gem_userptr_set_active(struct drm_i915_gem_object *obj,
			      bool value)
{
	int ret = 0;

	/* During mm_invalidate_range we need to cancel any userptr that
	 * overlaps the range being invalidated. Doing so requires the
	 * struct_mutex, and that risks recursion. In order to cause
	 * recursion, the user must alias the userptr address space with
	 * a GTT mmapping (possible with a MAP_FIXED) - then when we have
	 * to invalidate that mmaping, mm_invalidate_range is called with
	 * the userptr address *and* the struct_mutex held.  To prevent that
	 * we set a flag under the i915_mmu_notifier spinlock to indicate
	 * whether this object is valid.
	 */
#if defined(CONFIG_MMU_NOTIFIER)
	if (obj->userptr.mmu_object == NULL)
		return 0;

	spin_lock(&obj->userptr.mmu_object->mn->lock);
	/* In order to serialise get_pages with an outstanding
	 * cancel_userptr, we must drop the struct_mutex and try again.
	 */
	if (!value)
		del_object(obj->userptr.mmu_object);
	else if (!work_pending(&obj->userptr.mmu_object->work))
		add_object(obj->userptr.mmu_object);
	else
		ret = -EAGAIN;
	spin_unlock(&obj->userptr.mmu_object->mn->lock);
#endif

	return ret;
}
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
struct TYPE_2__ {scalar_t__ madv; int /*<<< orphan*/  pages_pin_count; } ;
struct drm_i915_gem_object {TYPE_1__ mm; int /*<<< orphan*/  pin_global; int /*<<< orphan*/  bind_count; } ;

/* Variables and functions */
 scalar_t__ I915_MADV_DONTNEED ; 
 scalar_t__ READ_ONCE (int /*<<< orphan*/ ) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i915_gem_object_is_shrinkable (struct drm_i915_gem_object*) ; 
 scalar_t__ swap_available () ; 

__attribute__((used)) static bool can_release_pages(struct drm_i915_gem_object *obj)
{
	/* Consider only shrinkable ojects. */
	if (!i915_gem_object_is_shrinkable(obj))
		return false;

	/* Only report true if by unbinding the object and putting its pages
	 * we can actually make forward progress towards freeing physical
	 * pages.
	 *
	 * If the pages are pinned for any other reason than being bound
	 * to the GPU, simply unbinding from the GPU is not going to succeed
	 * in releasing our pin count on the pages themselves.
	 */
	if (atomic_read(&obj->mm.pages_pin_count) > atomic_read(&obj->bind_count))
		return false;

	/* If any vma are "permanently" pinned, it will prevent us from
	 * reclaiming the obj->mm.pages. We only allow scanout objects to claim
	 * a permanent pin, along with a few others like the context objects.
	 * To simplify the scan, and to avoid walking the list of vma under the
	 * object, we just check the count of its permanently pinned.
	 */
	if (READ_ONCE(obj->pin_global))
		return false;

	/* We can only return physical pages to the system if we can either
	 * discard the contents (because the user has marked them as being
	 * purgeable) or if we can move their contents out to swap.
	 */
	return swap_available() || obj->mm.madv == I915_MADV_DONTNEED;
}
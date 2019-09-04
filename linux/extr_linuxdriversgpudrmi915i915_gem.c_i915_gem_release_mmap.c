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
struct TYPE_4__ {int /*<<< orphan*/  struct_mutex; } ;
struct drm_i915_private {TYPE_2__ drm; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;
struct drm_i915_gem_object {int /*<<< orphan*/  userfault_count; TYPE_1__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  __i915_gem_object_release_mmap (struct drm_i915_gem_object*) ; 
 int /*<<< orphan*/  intel_runtime_pm_get (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_runtime_pm_put (struct drm_i915_private*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmb () ; 

void
i915_gem_release_mmap(struct drm_i915_gem_object *obj)
{
	struct drm_i915_private *i915 = to_i915(obj->base.dev);

	/* Serialisation between user GTT access and our code depends upon
	 * revoking the CPU's PTE whilst the mutex is held. The next user
	 * pagefault then has to wait until we release the mutex.
	 *
	 * Note that RPM complicates somewhat by adding an additional
	 * requirement that operations to the GGTT be made holding the RPM
	 * wakeref.
	 */
	lockdep_assert_held(&i915->drm.struct_mutex);
	intel_runtime_pm_get(i915);

	if (!obj->userfault_count)
		goto out;

	__i915_gem_object_release_mmap(obj);

	/* Ensure that the CPU's PTE are revoked and there are not outstanding
	 * memory transactions from userspace before we return. The TLB
	 * flushing implied above by changing the PTE above *should* be
	 * sufficient, an extra barrier here just provides us with a bit
	 * of paranoid documentation about our requirement to serialise
	 * memory writes before touching registers / GSM.
	 */
	wmb();

out:
	intel_runtime_pm_put(i915);
}
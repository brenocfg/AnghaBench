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
struct hang {int /*<<< orphan*/  i915; int /*<<< orphan*/  ctx; int /*<<< orphan*/  hws; int /*<<< orphan*/  obj; int /*<<< orphan*/ * batch; } ;

/* Variables and functions */
 int /*<<< orphan*/  I915_WAIT_LOCKED ; 
 int /*<<< orphan*/  MI_BATCH_BUFFER_END ; 
 int /*<<< orphan*/  i915_gem_chipset_flush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_gem_object_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_gem_object_unpin_map (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  igt_flush_test (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kernel_context_close (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hang_fini(struct hang *h)
{
	*h->batch = MI_BATCH_BUFFER_END;
	i915_gem_chipset_flush(h->i915);

	i915_gem_object_unpin_map(h->obj);
	i915_gem_object_put(h->obj);

	i915_gem_object_unpin_map(h->hws);
	i915_gem_object_put(h->hws);

	kernel_context_close(h->ctx);

	igt_flush_test(h->i915, I915_WAIT_LOCKED);
}
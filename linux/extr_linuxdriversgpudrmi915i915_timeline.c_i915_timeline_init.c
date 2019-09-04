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
struct i915_timeline {char const* name; int /*<<< orphan*/  sync; int /*<<< orphan*/  requests; int /*<<< orphan*/  last_request; int /*<<< orphan*/  lock; int /*<<< orphan*/  fence_context; int /*<<< orphan*/  link; } ;
struct TYPE_3__ {int /*<<< orphan*/  timelines; } ;
struct TYPE_4__ {int /*<<< orphan*/  struct_mutex; } ;
struct drm_i915_private {TYPE_1__ gt; TYPE_2__ drm; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 scalar_t__ I915_NUM_ENGINES ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ KSYNCMAP ; 
 int /*<<< orphan*/  dma_fence_context_alloc (int) ; 
 int /*<<< orphan*/  i915_syncmap_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_request_active (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

void i915_timeline_init(struct drm_i915_private *i915,
			struct i915_timeline *timeline,
			const char *name)
{
	lockdep_assert_held(&i915->drm.struct_mutex);

	/*
	 * Ideally we want a set of engines on a single leaf as we expect
	 * to mostly be tracking synchronisation between engines. It is not
	 * a huge issue if this is not the case, but we may want to mitigate
	 * any page crossing penalties if they become an issue.
	 */
	BUILD_BUG_ON(KSYNCMAP < I915_NUM_ENGINES);

	timeline->name = name;

	list_add(&timeline->link, &i915->gt.timelines);

	/* Called during early_init before we know how many engines there are */

	timeline->fence_context = dma_fence_context_alloc(1);

	spin_lock_init(&timeline->lock);

	init_request_active(&timeline->last_request, NULL);
	INIT_LIST_HEAD(&timeline->requests);

	i915_syncmap_init(&timeline->sync);
}
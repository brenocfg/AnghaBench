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
struct TYPE_2__ {int /*<<< orphan*/  struct_mutex; } ;
struct drm_i915_private {TYPE_1__ drm; } ;

/* Variables and functions */
 int /*<<< orphan*/  i915_gem_drain_freed_objects (struct drm_i915_private*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cleanup_freed_objects(struct drm_i915_private *i915)
{
	/*
	 * As we may hold onto the struct_mutex for inordinate lengths of
	 * time, the NMI khungtaskd detector may fire for the free objects
	 * worker.
	 */
	mutex_unlock(&i915->drm.struct_mutex);

	i915_gem_drain_freed_objects(i915);

	mutex_lock(&i915->drm.struct_mutex);
}
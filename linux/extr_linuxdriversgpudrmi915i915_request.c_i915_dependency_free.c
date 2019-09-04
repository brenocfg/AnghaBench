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
struct i915_dependency {int dummy; } ;
struct drm_i915_private {int /*<<< orphan*/  dependencies; } ;

/* Variables and functions */
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct i915_dependency*) ; 

__attribute__((used)) static void
i915_dependency_free(struct drm_i915_private *i915,
		     struct i915_dependency *dep)
{
	kmem_cache_free(i915->dependencies, dep);
}
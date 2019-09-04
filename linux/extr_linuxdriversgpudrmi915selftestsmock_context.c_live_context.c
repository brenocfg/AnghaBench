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
struct i915_gem_context {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  struct_mutex; } ;
struct drm_i915_private {TYPE_1__ drm; } ;
struct drm_file {int /*<<< orphan*/  driver_priv; } ;

/* Variables and functions */
 struct i915_gem_context* i915_gem_create_context (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

struct i915_gem_context *
live_context(struct drm_i915_private *i915, struct drm_file *file)
{
	lockdep_assert_held(&i915->drm.struct_mutex);

	return i915_gem_create_context(i915, file->driver_priv);
}
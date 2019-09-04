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
struct i915_gem_context {int dummy; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  I915_PRIORITY_NORMAL ; 
 struct i915_gem_context* i915_gem_context_create_kernel (struct drm_i915_private*,int /*<<< orphan*/ ) ; 

struct i915_gem_context *
kernel_context(struct drm_i915_private *i915)
{
	return i915_gem_context_create_kernel(i915, I915_PRIORITY_NORMAL);
}
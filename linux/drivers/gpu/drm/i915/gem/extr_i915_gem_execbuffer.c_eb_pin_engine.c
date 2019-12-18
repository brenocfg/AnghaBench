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
struct intel_context {int dummy; } ;
struct i915_execbuffer {int /*<<< orphan*/  gem_context; } ;
struct drm_i915_gem_execbuffer2 {unsigned int flags; } ;
struct drm_file {int dummy; } ;

/* Variables and functions */
 unsigned int I915_EXEC_RING_MASK ; 
 scalar_t__ IS_ERR (struct intel_context*) ; 
 int PTR_ERR (struct intel_context*) ; 
 int __eb_pin_engine (struct i915_execbuffer*,struct intel_context*) ; 
 unsigned int eb_select_legacy_ring (struct i915_execbuffer*,struct drm_file*,struct drm_i915_gem_execbuffer2*) ; 
 struct intel_context* i915_gem_context_get_engine (int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ i915_gem_context_user_engines (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_context_put (struct intel_context*) ; 

__attribute__((used)) static int
eb_pin_engine(struct i915_execbuffer *eb,
	      struct drm_file *file,
	      struct drm_i915_gem_execbuffer2 *args)
{
	struct intel_context *ce;
	unsigned int idx;
	int err;

	if (i915_gem_context_user_engines(eb->gem_context))
		idx = args->flags & I915_EXEC_RING_MASK;
	else
		idx = eb_select_legacy_ring(eb, file, args);

	ce = i915_gem_context_get_engine(eb->gem_context, idx);
	if (IS_ERR(ce))
		return PTR_ERR(ce);

	err = __eb_pin_engine(eb, ce);
	intel_context_put(ce);

	return err;
}
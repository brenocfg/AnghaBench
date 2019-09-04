#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct intel_engine_cs {int dummy; } ;
struct intel_context {int dummy; } ;
struct i915_gem_context {int dummy; } ;
struct TYPE_5__ {struct intel_context* pinned_ctx; } ;
struct TYPE_4__ {TYPE_2__ oa; } ;
struct TYPE_6__ {int /*<<< orphan*/  struct_mutex; } ;
struct drm_i915_private {TYPE_1__ perf; TYPE_3__ drm; struct intel_engine_cs** engine; } ;

/* Variables and functions */
 struct intel_context* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct intel_context*) ; 
 size_t RCS ; 
 int i915_mutex_lock_interruptible (TYPE_3__*) ; 
 struct intel_context* intel_context_pin (struct i915_gem_context*,struct intel_engine_cs*) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct intel_context *oa_pin_context(struct drm_i915_private *i915,
					    struct i915_gem_context *ctx)
{
	struct intel_engine_cs *engine = i915->engine[RCS];
	struct intel_context *ce;
	int ret;

	ret = i915_mutex_lock_interruptible(&i915->drm);
	if (ret)
		return ERR_PTR(ret);

	/*
	 * As the ID is the gtt offset of the context's vma we
	 * pin the vma to ensure the ID remains fixed.
	 *
	 * NB: implied RCS engine...
	 */
	ce = intel_context_pin(ctx, engine);
	mutex_unlock(&i915->drm.struct_mutex);
	if (IS_ERR(ce))
		return ce;

	i915->perf.oa.pinned_ctx = ce;

	return ce;
}
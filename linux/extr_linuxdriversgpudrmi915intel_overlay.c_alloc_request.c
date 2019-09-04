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
struct intel_overlay {struct drm_i915_private* i915; } ;
struct intel_engine_cs {int dummy; } ;
struct i915_request {int dummy; } ;
struct drm_i915_private {int /*<<< orphan*/  kernel_context; struct intel_engine_cs** engine; } ;

/* Variables and functions */
 size_t RCS ; 
 struct i915_request* i915_request_alloc (struct intel_engine_cs*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct i915_request *alloc_request(struct intel_overlay *overlay)
{
	struct drm_i915_private *dev_priv = overlay->i915;
	struct intel_engine_cs *engine = dev_priv->engine[RCS];

	return i915_request_alloc(engine, dev_priv->kernel_context);
}
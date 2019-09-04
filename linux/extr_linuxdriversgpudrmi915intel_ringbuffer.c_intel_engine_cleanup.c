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
struct intel_engine_cs {size_t id; int /*<<< orphan*/  (* cleanup ) (struct intel_engine_cs*) ;int /*<<< orphan*/  buffer; struct drm_i915_private* i915; } ;
struct drm_i915_private {int /*<<< orphan*/ ** engine; } ;

/* Variables and functions */
 int I915_READ_MODE (struct intel_engine_cs*) ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 int MODE_IDLE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  intel_engine_cleanup_common (struct intel_engine_cs*) ; 
 int /*<<< orphan*/  intel_ring_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_ring_unpin (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct intel_engine_cs*) ; 
 int /*<<< orphan*/  stub1 (struct intel_engine_cs*) ; 

void intel_engine_cleanup(struct intel_engine_cs *engine)
{
	struct drm_i915_private *dev_priv = engine->i915;

	WARN_ON(INTEL_GEN(dev_priv) > 2 &&
		(I915_READ_MODE(engine) & MODE_IDLE) == 0);

	intel_ring_unpin(engine->buffer);
	intel_ring_free(engine->buffer);

	if (engine->cleanup)
		engine->cleanup(engine);

	intel_engine_cleanup_common(engine);

	dev_priv->engine[engine->id] = NULL;
	kfree(engine);
}
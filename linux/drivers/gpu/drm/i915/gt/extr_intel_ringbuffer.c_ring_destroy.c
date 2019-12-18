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
struct TYPE_2__ {int /*<<< orphan*/  timeline; int /*<<< orphan*/  ring; } ;
struct intel_engine_cs {TYPE_1__ legacy; struct drm_i915_private* i915; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int ENGINE_READ (struct intel_engine_cs*,int /*<<< orphan*/ ) ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 int MODE_IDLE ; 
 int /*<<< orphan*/  RING_MI_MODE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  intel_engine_cleanup_common (struct intel_engine_cs*) ; 
 int /*<<< orphan*/  intel_ring_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_ring_unpin (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_timeline_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_timeline_unpin (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct intel_engine_cs*) ; 

__attribute__((used)) static void ring_destroy(struct intel_engine_cs *engine)
{
	struct drm_i915_private *dev_priv = engine->i915;

	WARN_ON(INTEL_GEN(dev_priv) > 2 &&
		(ENGINE_READ(engine, RING_MI_MODE) & MODE_IDLE) == 0);

	intel_engine_cleanup_common(engine);

	intel_ring_unpin(engine->legacy.ring);
	intel_ring_put(engine->legacy.ring);

	intel_timeline_unpin(engine->legacy.timeline);
	intel_timeline_put(engine->legacy.timeline);

	kfree(engine);
}
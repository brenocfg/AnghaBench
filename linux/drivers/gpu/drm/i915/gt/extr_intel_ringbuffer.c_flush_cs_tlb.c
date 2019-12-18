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
struct intel_engine_cs {int /*<<< orphan*/  name; int /*<<< orphan*/  mmio_base; int /*<<< orphan*/  uncore; struct drm_i915_private* i915; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int /*<<< orphan*/ ) ; 
 int ENGINE_READ (struct intel_engine_cs*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENGINE_WRITE (struct intel_engine_cs*,int /*<<< orphan*/  (*) (int /*<<< orphan*/ ),int /*<<< orphan*/ ) ; 
 int INSTPM_SYNC_FLUSH ; 
 int INSTPM_TLB_INVALIDATE ; 
 int /*<<< orphan*/  IS_GEN_RANGE (struct drm_i915_private*,int,int) ; 
 int MODE_IDLE ; 
 int /*<<< orphan*/  RING_INSTPM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RING_MI_MODE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  _MASKED_BIT_ENABLE (int) ; 
 scalar_t__ intel_wait_for_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void flush_cs_tlb(struct intel_engine_cs *engine)
{
	struct drm_i915_private *dev_priv = engine->i915;

	if (!IS_GEN_RANGE(dev_priv, 6, 7))
		return;

	/* ring should be idle before issuing a sync flush*/
	WARN_ON((ENGINE_READ(engine, RING_MI_MODE) & MODE_IDLE) == 0);

	ENGINE_WRITE(engine, RING_INSTPM,
		     _MASKED_BIT_ENABLE(INSTPM_TLB_INVALIDATE |
					INSTPM_SYNC_FLUSH));
	if (intel_wait_for_register(engine->uncore,
				    RING_INSTPM(engine->mmio_base),
				    INSTPM_SYNC_FLUSH, 0,
				    1000))
		DRM_ERROR("%s: wait for SyncFlush to complete for TLB invalidation timed out\n",
			  engine->name);
}
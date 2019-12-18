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
struct intel_ring {int head; int tail; int /*<<< orphan*/  vma; int /*<<< orphan*/  size; } ;
struct TYPE_2__ {struct intel_ring* ring; } ;
struct intel_engine_cs {int /*<<< orphan*/  uncore; int /*<<< orphan*/  name; int /*<<< orphan*/  mmio_base; TYPE_1__ legacy; struct drm_i915_private* i915; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int /*<<< orphan*/ ,int,int,int,int,...) ; 
 int EIO ; 
 int /*<<< orphan*/  ENGINE_POSTING_READ (struct intel_engine_cs*,int /*<<< orphan*/  (*) (int /*<<< orphan*/ )) ; 
 int ENGINE_READ (struct intel_engine_cs*,int /*<<< orphan*/  (*) (int /*<<< orphan*/ )) ; 
 int /*<<< orphan*/  ENGINE_WRITE (struct intel_engine_cs*,int /*<<< orphan*/  (*) (int /*<<< orphan*/ ),int) ; 
 int /*<<< orphan*/  FORCEWAKE_ALL ; 
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int /*<<< orphan*/  GEM_TRACE (char*,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ HWS_NEEDS_PHYSICAL (struct drm_i915_private*) ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 int /*<<< orphan*/  RING_CTL (int /*<<< orphan*/ ) ; 
 int RING_CTL_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RING_HEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RING_MI_MODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RING_START (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RING_TAIL (int /*<<< orphan*/ ) ; 
 int RING_VALID ; 
 int /*<<< orphan*/  STOP_RING ; 
 int _MASKED_BIT_DISABLE (int /*<<< orphan*/ ) ; 
 int i915_ggtt_offset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_engine_queue_breadcrumbs (struct intel_engine_cs*) ; 
 int /*<<< orphan*/  intel_engine_reset_breadcrumbs (struct intel_engine_cs*) ; 
 int /*<<< orphan*/  intel_ring_offset_valid (struct intel_ring*,int) ; 
 int /*<<< orphan*/  intel_ring_update_space (struct intel_ring*) ; 
 int /*<<< orphan*/  intel_uncore_forcewake_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_uncore_forcewake_put (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ intel_wait_for_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  ring_setup_phys_status_page (struct intel_engine_cs*) ; 
 int /*<<< orphan*/  ring_setup_status_page (struct intel_engine_cs*) ; 
 int /*<<< orphan*/  stop_ring (struct intel_engine_cs*) ; 

__attribute__((used)) static int xcs_resume(struct intel_engine_cs *engine)
{
	struct drm_i915_private *dev_priv = engine->i915;
	struct intel_ring *ring = engine->legacy.ring;
	int ret = 0;

	GEM_TRACE("%s: ring:{HEAD:%04x, TAIL:%04x}\n",
		  engine->name, ring->head, ring->tail);

	intel_uncore_forcewake_get(engine->uncore, FORCEWAKE_ALL);

	/* WaClearRingBufHeadRegAtInit:ctg,elk */
	if (!stop_ring(engine)) {
		/* G45 ring initialization often fails to reset head to zero */
		DRM_DEBUG_DRIVER("%s head not reset to zero "
				"ctl %08x head %08x tail %08x start %08x\n",
				engine->name,
				ENGINE_READ(engine, RING_CTL),
				ENGINE_READ(engine, RING_HEAD),
				ENGINE_READ(engine, RING_TAIL),
				ENGINE_READ(engine, RING_START));

		if (!stop_ring(engine)) {
			DRM_ERROR("failed to set %s head to zero "
				  "ctl %08x head %08x tail %08x start %08x\n",
				  engine->name,
				  ENGINE_READ(engine, RING_CTL),
				  ENGINE_READ(engine, RING_HEAD),
				  ENGINE_READ(engine, RING_TAIL),
				  ENGINE_READ(engine, RING_START));
			ret = -EIO;
			goto out;
		}
	}

	if (HWS_NEEDS_PHYSICAL(dev_priv))
		ring_setup_phys_status_page(engine);
	else
		ring_setup_status_page(engine);

	intel_engine_reset_breadcrumbs(engine);

	/* Enforce ordering by reading HEAD register back */
	ENGINE_POSTING_READ(engine, RING_HEAD);

	/*
	 * Initialize the ring. This must happen _after_ we've cleared the ring
	 * registers with the above sequence (the readback of the HEAD registers
	 * also enforces ordering), otherwise the hw might lose the new ring
	 * register values.
	 */
	ENGINE_WRITE(engine, RING_START, i915_ggtt_offset(ring->vma));

	/* Check that the ring offsets point within the ring! */
	GEM_BUG_ON(!intel_ring_offset_valid(ring, ring->head));
	GEM_BUG_ON(!intel_ring_offset_valid(ring, ring->tail));
	intel_ring_update_space(ring);

	/* First wake the ring up to an empty/idle ring */
	ENGINE_WRITE(engine, RING_HEAD, ring->head);
	ENGINE_WRITE(engine, RING_TAIL, ring->head);
	ENGINE_POSTING_READ(engine, RING_TAIL);

	ENGINE_WRITE(engine, RING_CTL, RING_CTL_SIZE(ring->size) | RING_VALID);

	/* If the head is still not zero, the ring is dead */
	if (intel_wait_for_register(engine->uncore,
				    RING_CTL(engine->mmio_base),
				    RING_VALID, RING_VALID,
				    50)) {
		DRM_ERROR("%s initialization failed "
			  "ctl %08x (valid? %d) head %08x [%08x] tail %08x [%08x] start %08x [expected %08x]\n",
			  engine->name,
			  ENGINE_READ(engine, RING_CTL),
			  ENGINE_READ(engine, RING_CTL) & RING_VALID,
			  ENGINE_READ(engine, RING_HEAD), ring->head,
			  ENGINE_READ(engine, RING_TAIL), ring->tail,
			  ENGINE_READ(engine, RING_START),
			  i915_ggtt_offset(ring->vma));
		ret = -EIO;
		goto out;
	}

	if (INTEL_GEN(dev_priv) > 2)
		ENGINE_WRITE(engine,
			     RING_MI_MODE, _MASKED_BIT_DISABLE(STOP_RING));

	/* Now awake, let it get started */
	if (ring->tail != ring->head) {
		ENGINE_WRITE(engine, RING_TAIL, ring->tail);
		ENGINE_POSTING_READ(engine, RING_TAIL);
	}

	/* Papering over lost _interrupts_ immediately following the restart */
	intel_engine_queue_breadcrumbs(engine);
out:
	intel_uncore_forcewake_put(engine->uncore, FORCEWAKE_ALL);

	return ret;
}
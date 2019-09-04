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
struct intel_ring {int dummy; } ;
struct intel_engine_cs {int /*<<< orphan*/  i915; struct intel_ring* buffer; int /*<<< orphan*/  name; } ;
typedef  struct intel_ring i915_timeline ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_BUG_ON (struct intel_ring*) ; 
 scalar_t__ HAS_BROKEN_CS_TLB (int /*<<< orphan*/ ) ; 
 unsigned int I830_WA_SIZE ; 
 int /*<<< orphan*/  I915_GTT_PAGE_SIZE ; 
 scalar_t__ IS_ERR (struct intel_ring*) ; 
 int PAGE_SIZE ; 
 int PTR_ERR (struct intel_ring*) ; 
 struct intel_ring* i915_timeline_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_timeline_put (struct intel_ring*) ; 
 int /*<<< orphan*/  intel_engine_cleanup_common (struct intel_engine_cs*) ; 
 int /*<<< orphan*/  intel_engine_cleanup_scratch (struct intel_engine_cs*) ; 
 struct intel_ring* intel_engine_create_ring (struct intel_engine_cs*,struct intel_ring*,int) ; 
 int intel_engine_create_scratch (struct intel_engine_cs*,unsigned int) ; 
 int intel_engine_init_common (struct intel_engine_cs*) ; 
 int /*<<< orphan*/  intel_engine_setup_common (struct intel_engine_cs*) ; 
 int /*<<< orphan*/  intel_ring_free (struct intel_ring*) ; 
 int intel_ring_pin (struct intel_ring*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_ring_unpin (struct intel_ring*) ; 

__attribute__((used)) static int intel_init_ring_buffer(struct intel_engine_cs *engine)
{
	struct i915_timeline *timeline;
	struct intel_ring *ring;
	unsigned int size;
	int err;

	intel_engine_setup_common(engine);

	timeline = i915_timeline_create(engine->i915, engine->name);
	if (IS_ERR(timeline)) {
		err = PTR_ERR(timeline);
		goto err;
	}

	ring = intel_engine_create_ring(engine, timeline, 32 * PAGE_SIZE);
	i915_timeline_put(timeline);
	if (IS_ERR(ring)) {
		err = PTR_ERR(ring);
		goto err;
	}

	/* Ring wraparound at offset 0 sometimes hangs. No idea why. */
	err = intel_ring_pin(ring, engine->i915, I915_GTT_PAGE_SIZE);
	if (err)
		goto err_ring;

	GEM_BUG_ON(engine->buffer);
	engine->buffer = ring;

	size = PAGE_SIZE;
	if (HAS_BROKEN_CS_TLB(engine->i915))
		size = I830_WA_SIZE;
	err = intel_engine_create_scratch(engine, size);
	if (err)
		goto err_unpin;

	err = intel_engine_init_common(engine);
	if (err)
		goto err_scratch;

	return 0;

err_scratch:
	intel_engine_cleanup_scratch(engine);
err_unpin:
	intel_ring_unpin(ring);
err_ring:
	intel_ring_free(ring);
err:
	intel_engine_cleanup_common(engine);
	return err;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct intel_ring {int size; int effective_size; struct i915_vma* vma; int /*<<< orphan*/  timeline; int /*<<< orphan*/  request_list; } ;
struct i915_timeline {int dummy; } ;
struct intel_engine_cs {TYPE_2__* i915; struct i915_timeline timeline; } ;
struct i915_vma {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  struct_mutex; } ;
struct TYPE_6__ {TYPE_1__ drm; } ;

/* Variables and functions */
 int CACHELINE_BYTES ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct intel_ring* ERR_CAST (struct i915_vma*) ; 
 struct intel_ring* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ERR (struct i915_vma*) ; 
 scalar_t__ IS_I830 (TYPE_2__*) ; 
 scalar_t__ IS_I845G (TYPE_2__*) ; 
 int RING_CTL_SIZE (int) ; 
 int RING_NR_PAGES ; 
 int /*<<< orphan*/  i915_timeline_get (struct i915_timeline*) ; 
 struct i915_vma* intel_ring_create_vma (TYPE_2__*,int) ; 
 int /*<<< orphan*/  intel_ring_update_space (struct intel_ring*) ; 
 int /*<<< orphan*/  is_power_of_2 (int) ; 
 int /*<<< orphan*/  kfree (struct intel_ring*) ; 
 struct intel_ring* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

struct intel_ring *
intel_engine_create_ring(struct intel_engine_cs *engine,
			 struct i915_timeline *timeline,
			 int size)
{
	struct intel_ring *ring;
	struct i915_vma *vma;

	GEM_BUG_ON(!is_power_of_2(size));
	GEM_BUG_ON(RING_CTL_SIZE(size) & ~RING_NR_PAGES);
	GEM_BUG_ON(timeline == &engine->timeline);
	lockdep_assert_held(&engine->i915->drm.struct_mutex);

	ring = kzalloc(sizeof(*ring), GFP_KERNEL);
	if (!ring)
		return ERR_PTR(-ENOMEM);

	INIT_LIST_HEAD(&ring->request_list);
	ring->timeline = i915_timeline_get(timeline);

	ring->size = size;
	/* Workaround an erratum on the i830 which causes a hang if
	 * the TAIL pointer points to within the last 2 cachelines
	 * of the buffer.
	 */
	ring->effective_size = size;
	if (IS_I830(engine->i915) || IS_I845G(engine->i915))
		ring->effective_size -= 2 * CACHELINE_BYTES;

	intel_ring_update_space(ring);

	vma = intel_ring_create_vma(engine->i915, size);
	if (IS_ERR(vma)) {
		kfree(ring);
		return ERR_CAST(vma);
	}
	ring->vma = vma;

	return ring;
}
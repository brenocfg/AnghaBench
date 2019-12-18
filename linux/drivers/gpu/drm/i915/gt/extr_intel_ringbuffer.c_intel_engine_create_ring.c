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
struct intel_ring {int size; int effective_size; struct i915_vma* vma; int /*<<< orphan*/  ref; } ;
struct intel_engine_cs {TYPE_1__* gt; struct drm_i915_private* i915; } ;
struct i915_vma {int dummy; } ;
struct drm_i915_private {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  ggtt; } ;

/* Variables and functions */
 int CACHELINE_BYTES ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct intel_ring* ERR_CAST (struct i915_vma*) ; 
 struct intel_ring* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct i915_vma*) ; 
 scalar_t__ IS_I830 (struct drm_i915_private*) ; 
 scalar_t__ IS_I845G (struct drm_i915_private*) ; 
 int RING_CTL_SIZE (int) ; 
 int RING_NR_PAGES ; 
 struct i915_vma* create_ring_vma (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  intel_ring_update_space (struct intel_ring*) ; 
 int /*<<< orphan*/  is_power_of_2 (int) ; 
 int /*<<< orphan*/  kfree (struct intel_ring*) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 struct intel_ring* kzalloc (int,int /*<<< orphan*/ ) ; 

struct intel_ring *
intel_engine_create_ring(struct intel_engine_cs *engine, int size)
{
	struct drm_i915_private *i915 = engine->i915;
	struct intel_ring *ring;
	struct i915_vma *vma;

	GEM_BUG_ON(!is_power_of_2(size));
	GEM_BUG_ON(RING_CTL_SIZE(size) & ~RING_NR_PAGES);

	ring = kzalloc(sizeof(*ring), GFP_KERNEL);
	if (!ring)
		return ERR_PTR(-ENOMEM);

	kref_init(&ring->ref);

	ring->size = size;
	/* Workaround an erratum on the i830 which causes a hang if
	 * the TAIL pointer points to within the last 2 cachelines
	 * of the buffer.
	 */
	ring->effective_size = size;
	if (IS_I830(i915) || IS_I845G(i915))
		ring->effective_size -= 2 * CACHELINE_BYTES;

	intel_ring_update_space(ring);

	vma = create_ring_vma(engine->gt->ggtt, size);
	if (IS_ERR(vma)) {
		kfree(ring);
		return ERR_CAST(vma);
	}
	ring->vma = vma;

	return ring;
}
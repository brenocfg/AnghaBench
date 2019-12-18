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
struct intel_ring {int /*<<< orphan*/ * vaddr; int /*<<< orphan*/  emit; int /*<<< orphan*/  pin_count; struct i915_vma* vma; } ;
struct i915_vma {int /*<<< orphan*/  obj; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int /*<<< orphan*/  atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i915_gem_object_unpin_map (int /*<<< orphan*/ ) ; 
 scalar_t__ i915_vma_is_map_and_fenceable (struct i915_vma*) ; 
 int /*<<< orphan*/  i915_vma_make_purgeable (struct i915_vma*) ; 
 int /*<<< orphan*/  i915_vma_unpin (struct i915_vma*) ; 
 int /*<<< orphan*/  i915_vma_unpin_iomap (struct i915_vma*) ; 
 int /*<<< orphan*/  i915_vma_unset_ggtt_write (struct i915_vma*) ; 
 int /*<<< orphan*/  intel_ring_reset (struct intel_ring*,int /*<<< orphan*/ ) ; 

void intel_ring_unpin(struct intel_ring *ring)
{
	struct i915_vma *vma = ring->vma;

	if (!atomic_dec_and_test(&ring->pin_count))
		return;

	/* Discard any unused bytes beyond that submitted to hw. */
	intel_ring_reset(ring, ring->emit);

	i915_vma_unset_ggtt_write(vma);
	if (i915_vma_is_map_and_fenceable(vma))
		i915_vma_unpin_iomap(vma);
	else
		i915_gem_object_unpin_map(vma->obj);

	GEM_BUG_ON(!ring->vaddr);
	ring->vaddr = NULL;

	i915_vma_unpin(vma);
	i915_vma_make_purgeable(vma);
}
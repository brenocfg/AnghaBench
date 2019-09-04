#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct intel_ring {TYPE_1__* vma; int /*<<< orphan*/ * vaddr; int /*<<< orphan*/  tail; } ;
struct TYPE_6__ {int /*<<< orphan*/  pin_global; } ;
struct TYPE_5__ {TYPE_4__* obj; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int /*<<< orphan*/  i915_gem_object_unpin_map (TYPE_4__*) ; 
 scalar_t__ i915_vma_is_map_and_fenceable (TYPE_1__*) ; 
 int /*<<< orphan*/  i915_vma_unpin (TYPE_1__*) ; 
 int /*<<< orphan*/  i915_vma_unpin_iomap (TYPE_1__*) ; 
 int /*<<< orphan*/  intel_ring_reset (struct intel_ring*,int /*<<< orphan*/ ) ; 

void intel_ring_unpin(struct intel_ring *ring)
{
	GEM_BUG_ON(!ring->vma);
	GEM_BUG_ON(!ring->vaddr);

	/* Discard any unused bytes beyond that submitted to hw. */
	intel_ring_reset(ring, ring->tail);

	if (i915_vma_is_map_and_fenceable(ring->vma))
		i915_vma_unpin_iomap(ring->vma);
	else
		i915_gem_object_unpin_map(ring->vma->obj);
	ring->vaddr = NULL;

	ring->vma->obj->pin_global--;
	i915_vma_unpin(ring->vma);
}
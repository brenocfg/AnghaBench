#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct intel_context {int /*<<< orphan*/  gem_context; TYPE_1__* state; int /*<<< orphan*/  ring; } ;
struct TYPE_4__ {int /*<<< orphan*/  pin_global; } ;
struct TYPE_3__ {TYPE_2__* obj; } ;

/* Variables and functions */
 int /*<<< orphan*/  i915_gem_context_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_gem_object_unpin_map (TYPE_2__*) ; 
 int /*<<< orphan*/  i915_vma_unpin (TYPE_1__*) ; 
 int /*<<< orphan*/  intel_ring_unpin (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void execlists_context_unpin(struct intel_context *ce)
{
	intel_ring_unpin(ce->ring);

	ce->state->obj->pin_global--;
	i915_gem_object_unpin_map(ce->state->obj);
	i915_vma_unpin(ce->state);

	i915_gem_context_put(ce->gem_context);
}
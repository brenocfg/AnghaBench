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
struct intel_context {TYPE_2__* ring; TYPE_1__* state; int /*<<< orphan*/  gem_context; int /*<<< orphan*/  engine; scalar_t__ lrc_reg_state; } ;
struct TYPE_4__ {int /*<<< orphan*/  tail; } ;
struct TYPE_3__ {int /*<<< orphan*/  obj; } ;

/* Variables and functions */
 int LRC_STATE_PN ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  check_redzone (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_gem_context_unpin_hw_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_gem_object_unpin_map (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_ring_reset (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void execlists_context_unpin(struct intel_context *ce)
{
	check_redzone((void *)ce->lrc_reg_state - LRC_STATE_PN * PAGE_SIZE,
		      ce->engine);

	i915_gem_context_unpin_hw_id(ce->gem_context);
	i915_gem_object_unpin_map(ce->state->obj);
	intel_ring_reset(ce->ring, ce->ring->tail);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct intel_engine_cs {scalar_t__ context_size; scalar_t__ pinned_default_state; } ;
struct intel_context {TYPE_1__* ring; int /*<<< orphan*/ * lrc_reg_state; } ;
struct TYPE_3__ {int /*<<< orphan*/  head; } ;

/* Variables and functions */
 int LRC_STATE_PN ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  __execlists_update_reg_state (struct intel_context*,struct intel_engine_cs*) ; 
 int /*<<< orphan*/  execlists_init_reg_state (int /*<<< orphan*/ *,struct intel_context*,struct intel_engine_cs*,TYPE_1__*) ; 
 int /*<<< orphan*/  intel_ring_update_space (TYPE_1__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 

void intel_lr_context_reset(struct intel_engine_cs *engine,
			    struct intel_context *ce,
			    u32 head,
			    bool scrub)
{
	/*
	 * We want a simple context + ring to execute the breadcrumb update.
	 * We cannot rely on the context being intact across the GPU hang,
	 * so clear it and rebuild just what we need for the breadcrumb.
	 * All pending requests for this context will be zapped, and any
	 * future request will be after userspace has had the opportunity
	 * to recreate its own state.
	 */
	if (scrub) {
		u32 *regs = ce->lrc_reg_state;

		if (engine->pinned_default_state) {
			memcpy(regs, /* skip restoring the vanilla PPHWSP */
			       engine->pinned_default_state + LRC_STATE_PN * PAGE_SIZE,
			       engine->context_size - PAGE_SIZE);
		}
		execlists_init_reg_state(regs, ce, engine, ce->ring);
	}

	/* Rerun the request; its payload has been neutered (if guilty). */
	ce->ring->head = head;
	intel_ring_update_space(ce->ring);

	__execlists_update_reg_state(ce, engine);
}
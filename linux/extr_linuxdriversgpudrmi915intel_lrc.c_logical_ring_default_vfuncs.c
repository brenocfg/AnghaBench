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
struct TYPE_2__ {int /*<<< orphan*/  finish; int /*<<< orphan*/  reset; int /*<<< orphan*/  prepare; } ;
struct intel_engine_cs {int /*<<< orphan*/  emit_bb_start; int /*<<< orphan*/  irq_disable; int /*<<< orphan*/  irq_enable; int /*<<< orphan*/  i915; int /*<<< orphan*/  set_default_submission; int /*<<< orphan*/  emit_breadcrumb_sz; int /*<<< orphan*/  emit_breadcrumb; int /*<<< orphan*/  emit_flush; int /*<<< orphan*/  request_alloc; int /*<<< orphan*/  context_pin; TYPE_1__ reset; int /*<<< orphan*/  init_hw; } ;

/* Variables and functions */
 int INTEL_GEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  execlists_context_pin ; 
 int /*<<< orphan*/  execlists_request_alloc ; 
 int /*<<< orphan*/  execlists_reset ; 
 int /*<<< orphan*/  execlists_reset_finish ; 
 int /*<<< orphan*/  execlists_reset_prepare ; 
 int /*<<< orphan*/  gen8_emit_bb_start ; 
 int /*<<< orphan*/  gen8_emit_breadcrumb ; 
 int /*<<< orphan*/  gen8_emit_breadcrumb_sz ; 
 int /*<<< orphan*/  gen8_emit_flush ; 
 int /*<<< orphan*/  gen8_init_common_ring ; 
 int /*<<< orphan*/  gen8_logical_ring_disable_irq ; 
 int /*<<< orphan*/  gen8_logical_ring_enable_irq ; 
 int /*<<< orphan*/  intel_execlists_set_default_submission ; 

__attribute__((used)) static void
logical_ring_default_vfuncs(struct intel_engine_cs *engine)
{
	/* Default vfuncs which can be overriden by each engine. */
	engine->init_hw = gen8_init_common_ring;

	engine->reset.prepare = execlists_reset_prepare;
	engine->reset.reset = execlists_reset;
	engine->reset.finish = execlists_reset_finish;

	engine->context_pin = execlists_context_pin;
	engine->request_alloc = execlists_request_alloc;

	engine->emit_flush = gen8_emit_flush;
	engine->emit_breadcrumb = gen8_emit_breadcrumb;
	engine->emit_breadcrumb_sz = gen8_emit_breadcrumb_sz;

	engine->set_default_submission = intel_execlists_set_default_submission;

	if (INTEL_GEN(engine->i915) < 11) {
		engine->irq_enable = gen8_logical_ring_enable_irq;
		engine->irq_disable = gen8_logical_ring_disable_irq;
	} else {
		/*
		 * TODO: On Gen11 interrupt masks need to be clear
		 * to allow C6 entry. Keep interrupts enabled at
		 * and take the hit of generating extra interrupts
		 * until a more refined solution exists.
		 */
	}
	engine->emit_bb_start = gen8_emit_bb_start;
}
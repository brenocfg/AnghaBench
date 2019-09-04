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
struct intel_engine_cs {TYPE_1__* i915; int /*<<< orphan*/  (* irq_enable ) (struct intel_engine_cs*) ;int /*<<< orphan*/  irq_posted; } ;
struct TYPE_2__ {int /*<<< orphan*/  irq_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENGINE_IRQ_BREADCRUMB ; 
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int /*<<< orphan*/  intel_irqs_enabled (TYPE_1__*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct intel_engine_cs*) ; 

__attribute__((used)) static void irq_enable(struct intel_engine_cs *engine)
{
	/*
	 * FIXME: Ideally we want this on the API boundary, but for the
	 * sake of testing with mock breadcrumbs (no HW so unable to
	 * enable irqs) we place it deep within the bowels, at the point
	 * of no return.
	 */
	GEM_BUG_ON(!intel_irqs_enabled(engine->i915));

	/* Enabling the IRQ may miss the generation of the interrupt, but
	 * we still need to force the barrier before reading the seqno,
	 * just in case.
	 */
	set_bit(ENGINE_IRQ_BREADCRUMB, &engine->irq_posted);

	/* Caller disables interrupts */
	if (engine->irq_enable) {
		spin_lock(&engine->i915->irq_lock);
		engine->irq_enable(engine);
		spin_unlock(&engine->i915->irq_lock);
	}
}
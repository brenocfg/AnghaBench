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
struct intel_breadcrumbs {int /*<<< orphan*/  irq_lock; scalar_t__ irq_enabled; } ;
struct intel_engine_cs {int /*<<< orphan*/  irq_posted; TYPE_2__* i915; int /*<<< orphan*/  id; struct intel_breadcrumbs breadcrumbs; } ;
struct TYPE_3__ {int /*<<< orphan*/  missed_irq_rings; } ;
struct TYPE_4__ {TYPE_1__ gpu_error; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENGINE_IRQ_BREADCRUMB ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  irq_disable (struct intel_engine_cs*) ; 
 int /*<<< orphan*/  irq_enable (struct intel_engine_cs*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void intel_engine_reset_breadcrumbs(struct intel_engine_cs *engine)
{
	struct intel_breadcrumbs *b = &engine->breadcrumbs;
	unsigned long flags;

	spin_lock_irqsave(&b->irq_lock, flags);

	/*
	 * Leave the fake_irq timer enabled (if it is running), but clear the
	 * bit so that it turns itself off on its next wake up and goes back
	 * to the long hangcheck interval if still required.
	 */
	clear_bit(engine->id, &engine->i915->gpu_error.missed_irq_rings);

	if (b->irq_enabled)
		irq_enable(engine);
	else
		irq_disable(engine);

	/*
	 * We set the IRQ_BREADCRUMB bit when we enable the irq presuming the
	 * GPU is active and may have already executed the MI_USER_INTERRUPT
	 * before the CPU is ready to receive. However, the engine is currently
	 * idle (we haven't started it yet), there is no possibility for a
	 * missed interrupt as we enabled the irq and so we can clear the
	 * immediate wakeup (until a real interrupt arrives for the waiter).
	 */
	clear_bit(ENGINE_IRQ_BREADCRUMB, &engine->irq_posted);

	spin_unlock_irqrestore(&b->irq_lock, flags);
}
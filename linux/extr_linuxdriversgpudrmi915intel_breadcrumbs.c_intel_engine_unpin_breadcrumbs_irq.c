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
struct intel_breadcrumbs {int /*<<< orphan*/  irq_lock; int /*<<< orphan*/  irq_enabled; } ;
struct intel_engine_cs {struct intel_breadcrumbs breadcrumbs; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int /*<<< orphan*/  irq_disable (struct intel_engine_cs*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

void intel_engine_unpin_breadcrumbs_irq(struct intel_engine_cs *engine)
{
	struct intel_breadcrumbs *b = &engine->breadcrumbs;

	spin_lock_irq(&b->irq_lock);
	GEM_BUG_ON(!b->irq_enabled); /* no underflow! */
	if (!--b->irq_enabled)
		irq_disable(engine);
	spin_unlock_irq(&b->irq_lock);
}
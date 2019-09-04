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
struct intel_breadcrumbs {int irq_wait; int irq_armed; int /*<<< orphan*/  irq_enabled; int /*<<< orphan*/  irq_lock; } ;
struct intel_engine_cs {struct intel_breadcrumbs breadcrumbs; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int /*<<< orphan*/  irq_disable (struct intel_engine_cs*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

void __intel_engine_disarm_breadcrumbs(struct intel_engine_cs *engine)
{
	struct intel_breadcrumbs *b = &engine->breadcrumbs;

	lockdep_assert_held(&b->irq_lock);
	GEM_BUG_ON(b->irq_wait);
	GEM_BUG_ON(!b->irq_armed);

	GEM_BUG_ON(!b->irq_enabled);
	if (!--b->irq_enabled)
		irq_disable(engine);

	b->irq_armed = false;
}
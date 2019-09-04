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
struct timer_list {int dummy; } ;
struct intel_breadcrumbs {unsigned int hangcheck_interrupts; int /*<<< orphan*/  hangcheck; int /*<<< orphan*/  fake_irq; int /*<<< orphan*/  irq_count; int /*<<< orphan*/  irq_armed; } ;
struct intel_engine_cs {struct intel_breadcrumbs breadcrumbs; } ;
struct TYPE_2__ {int /*<<< orphan*/  hangcheck; } ;

/* Variables and functions */
 int ENGINE_WAKEUP_ASLEEP ; 
 unsigned int READ_ONCE (int /*<<< orphan*/ ) ; 
 TYPE_1__ breadcrumbs ; 
 struct intel_engine_cs* engine ; 
 struct intel_engine_cs* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int intel_engine_wakeup (struct intel_engine_cs*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  missed_breadcrumb (struct intel_engine_cs*) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ wait_timeout () ; 

__attribute__((used)) static void intel_breadcrumbs_hangcheck(struct timer_list *t)
{
	struct intel_engine_cs *engine =
		from_timer(engine, t, breadcrumbs.hangcheck);
	struct intel_breadcrumbs *b = &engine->breadcrumbs;
	unsigned int irq_count;

	if (!b->irq_armed)
		return;

	irq_count = READ_ONCE(b->irq_count);
	if (b->hangcheck_interrupts != irq_count) {
		b->hangcheck_interrupts = irq_count;
		mod_timer(&b->hangcheck, wait_timeout());
		return;
	}

	/* We keep the hangcheck timer alive until we disarm the irq, even
	 * if there are no waiters at present.
	 *
	 * If the waiter was currently running, assume it hasn't had a chance
	 * to process the pending interrupt (e.g, low priority task on a loaded
	 * system) and wait until it sleeps before declaring a missed interrupt.
	 *
	 * If the waiter was asleep (and not even pending a wakeup), then we
	 * must have missed an interrupt as the GPU has stopped advancing
	 * but we still have a waiter. Assuming all batches complete within
	 * DRM_I915_HANGCHECK_JIFFIES [1.5s]!
	 */
	if (intel_engine_wakeup(engine) & ENGINE_WAKEUP_ASLEEP) {
		missed_breadcrumb(engine);
		mod_timer(&b->fake_irq, jiffies + 1);
	} else {
		mod_timer(&b->hangcheck, wait_timeout());
	}
}
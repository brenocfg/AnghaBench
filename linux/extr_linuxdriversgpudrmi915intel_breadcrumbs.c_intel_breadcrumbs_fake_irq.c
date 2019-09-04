#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct timer_list {int dummy; } ;
struct intel_breadcrumbs {int /*<<< orphan*/  fake_irq; int /*<<< orphan*/  hangcheck; scalar_t__ irq_armed; int /*<<< orphan*/  irq_lock; } ;
struct intel_engine_cs {TYPE_2__* i915; int /*<<< orphan*/  id; struct intel_breadcrumbs breadcrumbs; } ;
struct TYPE_6__ {int /*<<< orphan*/  fake_irq; } ;
struct TYPE_4__ {int /*<<< orphan*/  missed_irq_rings; } ;
struct TYPE_5__ {TYPE_1__ gpu_error; } ;

/* Variables and functions */
 int /*<<< orphan*/  __intel_breadcrumbs_wakeup (struct intel_breadcrumbs*) ; 
 int /*<<< orphan*/  __intel_engine_disarm_breadcrumbs (struct intel_engine_cs*) ; 
 TYPE_3__ breadcrumbs ; 
 struct intel_engine_cs* engine ; 
 struct intel_engine_cs* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ wait_timeout () ; 

__attribute__((used)) static void intel_breadcrumbs_fake_irq(struct timer_list *t)
{
	struct intel_engine_cs *engine =
		from_timer(engine, t, breadcrumbs.fake_irq);
	struct intel_breadcrumbs *b = &engine->breadcrumbs;

	/*
	 * The timer persists in case we cannot enable interrupts,
	 * or if we have previously seen seqno/interrupt incoherency
	 * ("missed interrupt" syndrome, better known as a "missed breadcrumb").
	 * Here the worker will wake up every jiffie in order to kick the
	 * oldest waiter to do the coherent seqno check.
	 */

	spin_lock_irq(&b->irq_lock);
	if (b->irq_armed && !__intel_breadcrumbs_wakeup(b))
		__intel_engine_disarm_breadcrumbs(engine);
	spin_unlock_irq(&b->irq_lock);
	if (!b->irq_armed)
		return;

	/* If the user has disabled the fake-irq, restore the hangchecking */
	if (!test_bit(engine->id, &engine->i915->gpu_error.missed_irq_rings)) {
		mod_timer(&b->hangcheck, wait_timeout());
		return;
	}

	mod_timer(&b->fake_irq, jiffies + 1);
}
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
struct intel_wait {scalar_t__ seqno; } ;
struct intel_breadcrumbs {int /*<<< orphan*/  rb_lock; } ;
struct intel_engine_cs {struct intel_breadcrumbs breadcrumbs; } ;

/* Variables and functions */
 int __intel_engine_add_wait (struct intel_engine_cs*,struct intel_wait*) ; 
 int i915_seqno_passed (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  intel_engine_get_seqno (struct intel_engine_cs*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

bool intel_engine_add_wait(struct intel_engine_cs *engine,
			   struct intel_wait *wait)
{
	struct intel_breadcrumbs *b = &engine->breadcrumbs;
	bool armed;

	spin_lock_irq(&b->rb_lock);
	armed = __intel_engine_add_wait(engine, wait);
	spin_unlock_irq(&b->rb_lock);
	if (armed)
		return armed;

	/* Make the caller recheck if its request has already started. */
	return i915_seqno_passed(intel_engine_get_seqno(engine),
				 wait->seqno - 1);
}
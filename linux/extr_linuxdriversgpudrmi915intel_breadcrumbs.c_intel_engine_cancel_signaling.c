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
struct intel_breadcrumbs {int /*<<< orphan*/  rb_lock; } ;
struct intel_engine_cs {struct intel_breadcrumbs breadcrumbs; } ;
struct TYPE_4__ {int /*<<< orphan*/  seqno; } ;
struct TYPE_3__ {int /*<<< orphan*/  link; TYPE_2__ wait; } ;
struct i915_request {TYPE_1__ signaling; int /*<<< orphan*/  lock; struct intel_engine_cs* engine; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int /*<<< orphan*/  READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __intel_engine_remove_wait (struct intel_engine_cs*,TYPE_2__*) ; 
 int /*<<< orphan*/  __list_del_entry (int /*<<< orphan*/ *) ; 
 scalar_t__ fetch_and_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  irqs_disabled () ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void intel_engine_cancel_signaling(struct i915_request *request)
{
	struct intel_engine_cs *engine = request->engine;
	struct intel_breadcrumbs *b = &engine->breadcrumbs;

	GEM_BUG_ON(!irqs_disabled());
	lockdep_assert_held(&request->lock);

	if (!READ_ONCE(request->signaling.wait.seqno))
		return;

	spin_lock(&b->rb_lock);
	__intel_engine_remove_wait(engine, &request->signaling.wait);
	if (fetch_and_zero(&request->signaling.wait.seqno))
		__list_del_entry(&request->signaling.link);
	spin_unlock(&b->rb_lock);
}
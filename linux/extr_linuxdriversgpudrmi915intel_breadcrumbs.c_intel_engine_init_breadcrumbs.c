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
struct task_struct {int dummy; } ;
struct intel_breadcrumbs {struct task_struct* signaler; int /*<<< orphan*/  signals; int /*<<< orphan*/  hangcheck; int /*<<< orphan*/  fake_irq; int /*<<< orphan*/  irq_lock; int /*<<< orphan*/  rb_lock; } ;
struct intel_engine_cs {int /*<<< orphan*/  id; struct intel_breadcrumbs breadcrumbs; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ERR (struct task_struct*) ; 
 int PTR_ERR (struct task_struct*) ; 
 int /*<<< orphan*/  intel_breadcrumbs_fake_irq ; 
 int /*<<< orphan*/  intel_breadcrumbs_hangcheck ; 
 int /*<<< orphan*/  intel_breadcrumbs_signaler ; 
 struct task_struct* kthread_run (int /*<<< orphan*/ ,struct intel_engine_cs*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int intel_engine_init_breadcrumbs(struct intel_engine_cs *engine)
{
	struct intel_breadcrumbs *b = &engine->breadcrumbs;
	struct task_struct *tsk;

	spin_lock_init(&b->rb_lock);
	spin_lock_init(&b->irq_lock);

	timer_setup(&b->fake_irq, intel_breadcrumbs_fake_irq, 0);
	timer_setup(&b->hangcheck, intel_breadcrumbs_hangcheck, 0);

	INIT_LIST_HEAD(&b->signals);

	/* Spawn a thread to provide a common bottom-half for all signals.
	 * As this is an asynchronous interface we cannot steal the current
	 * task for handling the bottom-half to the user interrupt, therefore
	 * we create a thread to do the coherent seqno dance after the
	 * interrupt and then signal the waitqueue (via the dma-buf/fence).
	 */
	tsk = kthread_run(intel_breadcrumbs_signaler, engine,
			  "i915/signal:%d", engine->id);
	if (IS_ERR(tsk))
		return PTR_ERR(tsk);

	b->signaler = tsk;

	return 0;
}
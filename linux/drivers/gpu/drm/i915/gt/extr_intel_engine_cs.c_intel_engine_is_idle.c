#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct tasklet_struct {int /*<<< orphan*/  data; int /*<<< orphan*/  (* func ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_9__ {int /*<<< orphan*/  rb_root; } ;
struct TYPE_10__ {TYPE_4__ queue; struct tasklet_struct tasklet; } ;
struct intel_engine_cs {TYPE_5__ execlists; TYPE_3__* i915; int /*<<< orphan*/  gt; } ;
struct TYPE_7__ {TYPE_1__* pdev; } ;
struct TYPE_8__ {TYPE_2__ drm; } ;
struct TYPE_6__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  RB_EMPTY_ROOT (int /*<<< orphan*/ *) ; 
 scalar_t__ __tasklet_is_enabled (struct tasklet_struct*) ; 
 scalar_t__ execlists_active (TYPE_5__*) ; 
 int /*<<< orphan*/  intel_engine_pm_is_awake (struct intel_engine_cs*) ; 
 scalar_t__ intel_gt_is_wedged (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_bh_disable () ; 
 int /*<<< orphan*/  local_bh_enable () ; 
 int ring_is_idle (struct intel_engine_cs*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  synchronize_hardirq (int /*<<< orphan*/ ) ; 
 scalar_t__ tasklet_trylock (struct tasklet_struct*) ; 
 int /*<<< orphan*/  tasklet_unlock (struct tasklet_struct*) ; 
 int /*<<< orphan*/  tasklet_unlock_wait (struct tasklet_struct*) ; 

bool intel_engine_is_idle(struct intel_engine_cs *engine)
{
	/* More white lies, if wedged, hw state is inconsistent */
	if (intel_gt_is_wedged(engine->gt))
		return true;

	if (!intel_engine_pm_is_awake(engine))
		return true;

	/* Waiting to drain ELSP? */
	if (execlists_active(&engine->execlists)) {
		struct tasklet_struct *t = &engine->execlists.tasklet;

		synchronize_hardirq(engine->i915->drm.pdev->irq);

		local_bh_disable();
		if (tasklet_trylock(t)) {
			/* Must wait for any GPU reset in progress. */
			if (__tasklet_is_enabled(t))
				t->func(t->data);
			tasklet_unlock(t);
		}
		local_bh_enable();

		/* Otherwise flush the tasklet if it was on another cpu */
		tasklet_unlock_wait(t);

		if (execlists_active(&engine->execlists))
			return false;
	}

	/* ELSP is empty, but there are ready requests? E.g. after reset */
	if (!RB_EMPTY_ROOT(&engine->execlists.queue.rb_root))
		return false;

	/* Ring stopped? */
	return ring_is_idle(engine);
}
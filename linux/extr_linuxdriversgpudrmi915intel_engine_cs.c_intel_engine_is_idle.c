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
struct tasklet_struct {int /*<<< orphan*/  data; int /*<<< orphan*/  (* func ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_5__ {int /*<<< orphan*/  rb_root; } ;
struct TYPE_6__ {TYPE_2__ queue; int /*<<< orphan*/  active; struct tasklet_struct tasklet; } ;
struct TYPE_4__ {int /*<<< orphan*/  mock; } ;
struct intel_engine_cs {TYPE_3__ execlists; TYPE_1__ breadcrumbs; struct drm_i915_private* i915; } ;
struct drm_i915_private {int /*<<< orphan*/  gpu_error; } ;

/* Variables and functions */
 scalar_t__ I915_SELFTEST_ONLY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RB_EMPTY_ROOT (int /*<<< orphan*/ *) ; 
 scalar_t__ READ_ONCE (int /*<<< orphan*/ ) ; 
 scalar_t__ __tasklet_is_enabled (struct tasklet_struct*) ; 
 int /*<<< orphan*/  i915_seqno_passed (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ i915_terminally_wedged (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_engine_get_seqno (struct intel_engine_cs*) ; 
 int /*<<< orphan*/  intel_engine_last_submit (struct intel_engine_cs*) ; 
 int /*<<< orphan*/  local_bh_disable () ; 
 int /*<<< orphan*/  local_bh_enable () ; 
 int /*<<< orphan*/  ring_is_idle (struct intel_engine_cs*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 scalar_t__ tasklet_trylock (struct tasklet_struct*) ; 
 int /*<<< orphan*/  tasklet_unlock (struct tasklet_struct*) ; 

bool intel_engine_is_idle(struct intel_engine_cs *engine)
{
	struct drm_i915_private *dev_priv = engine->i915;

	/* More white lies, if wedged, hw state is inconsistent */
	if (i915_terminally_wedged(&dev_priv->gpu_error))
		return true;

	/* Any inflight/incomplete requests? */
	if (!i915_seqno_passed(intel_engine_get_seqno(engine),
			       intel_engine_last_submit(engine)))
		return false;

	if (I915_SELFTEST_ONLY(engine->breadcrumbs.mock))
		return true;

	/* Waiting to drain ELSP? */
	if (READ_ONCE(engine->execlists.active)) {
		struct tasklet_struct *t = &engine->execlists.tasklet;

		local_bh_disable();
		if (tasklet_trylock(t)) {
			/* Must wait for any GPU reset in progress. */
			if (__tasklet_is_enabled(t))
				t->func(t->data);
			tasklet_unlock(t);
		}
		local_bh_enable();

		if (READ_ONCE(engine->execlists.active))
			return false;
	}

	/* ELSP is empty, but there are ready requests? E.g. after reset */
	if (!RB_EMPTY_ROOT(&engine->execlists.queue.rb_root))
		return false;

	/* Ring stopped? */
	if (!ring_is_idle(engine))
		return false;

	return true;
}
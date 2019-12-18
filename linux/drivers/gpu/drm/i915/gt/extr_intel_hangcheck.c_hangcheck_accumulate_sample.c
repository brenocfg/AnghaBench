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
struct TYPE_2__ {scalar_t__ action_timestamp; int /*<<< orphan*/  instdone; } ;
struct intel_engine_cs {TYPE_1__ hangcheck; } ;
struct hangcheck {int action; void* wedged; void* stalled; int /*<<< orphan*/  acthd; } ;

/* Variables and functions */
#define  ENGINE_ACTIVE_HEAD 134 
#define  ENGINE_ACTIVE_SEQNO 133 
#define  ENGINE_ACTIVE_SUBUNITS 132 
#define  ENGINE_DEAD 131 
#define  ENGINE_IDLE 130 
#define  ENGINE_WAIT 129 
#define  ENGINE_WAIT_KICK 128 
 unsigned long I915_ENGINE_DEAD_TIMEOUT ; 
 scalar_t__ I915_ENGINE_WEDGED_TIMEOUT ; 
 unsigned long I915_SEQNO_DEAD_TIMEOUT ; 
 int /*<<< orphan*/  MISSING_CASE (int) ; 
 int hangcheck_get_action (struct intel_engine_cs*,struct hangcheck*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 void* time_after (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void hangcheck_accumulate_sample(struct intel_engine_cs *engine,
					struct hangcheck *hc)
{
	unsigned long timeout = I915_ENGINE_DEAD_TIMEOUT;

	hc->action = hangcheck_get_action(engine, hc);

	/* We always increment the progress
	 * if the engine is busy and still processing
	 * the same request, so that no single request
	 * can run indefinitely (such as a chain of
	 * batches). The only time we do not increment
	 * the hangcheck score on this ring, if this
	 * engine is in a legitimate wait for another
	 * engine. In that case the waiting engine is a
	 * victim and we want to be sure we catch the
	 * right culprit. Then every time we do kick
	 * the ring, make it as a progress as the seqno
	 * advancement might ensure and if not, it
	 * will catch the hanging engine.
	 */

	switch (hc->action) {
	case ENGINE_IDLE:
	case ENGINE_ACTIVE_SEQNO:
		/* Clear head and subunit states on seqno movement */
		hc->acthd = 0;

		memset(&engine->hangcheck.instdone, 0,
		       sizeof(engine->hangcheck.instdone));

		/* Intentional fall through */
	case ENGINE_WAIT_KICK:
	case ENGINE_WAIT:
		engine->hangcheck.action_timestamp = jiffies;
		break;

	case ENGINE_ACTIVE_HEAD:
	case ENGINE_ACTIVE_SUBUNITS:
		/*
		 * Seqno stuck with still active engine gets leeway,
		 * in hopes that it is just a long shader.
		 */
		timeout = I915_SEQNO_DEAD_TIMEOUT;
		break;

	case ENGINE_DEAD:
		break;

	default:
		MISSING_CASE(hc->action);
	}

	hc->stalled = time_after(jiffies,
				 engine->hangcheck.action_timestamp + timeout);
	hc->wedged = time_after(jiffies,
				 engine->hangcheck.action_timestamp +
				 I915_ENGINE_WEDGED_TIMEOUT);
}
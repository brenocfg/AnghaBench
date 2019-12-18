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
struct TYPE_2__ {scalar_t__ last_ring; scalar_t__ last_head; } ;
struct intel_engine_cs {TYPE_1__ hangcheck; } ;
struct hangcheck {scalar_t__ ring; scalar_t__ head; int /*<<< orphan*/  acthd; } ;
typedef  enum intel_engine_hangcheck_action { ____Placeholder_intel_engine_hangcheck_action } intel_engine_hangcheck_action ;

/* Variables and functions */
 int ENGINE_ACTIVE_SEQNO ; 
 int ENGINE_IDLE ; 
 int engine_stuck (struct intel_engine_cs*,int /*<<< orphan*/ ) ; 
 scalar_t__ intel_engine_is_idle (struct intel_engine_cs*) ; 

__attribute__((used)) static enum intel_engine_hangcheck_action
hangcheck_get_action(struct intel_engine_cs *engine,
		     const struct hangcheck *hc)
{
	if (intel_engine_is_idle(engine))
		return ENGINE_IDLE;

	if (engine->hangcheck.last_ring != hc->ring)
		return ENGINE_ACTIVE_SEQNO;

	if (engine->hangcheck.last_head != hc->head)
		return ENGINE_ACTIVE_SEQNO;

	return engine_stuck(engine, hc->acthd);
}
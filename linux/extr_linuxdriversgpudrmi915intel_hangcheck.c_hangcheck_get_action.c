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
struct intel_engine_hangcheck {scalar_t__ seqno; int /*<<< orphan*/  acthd; } ;
struct TYPE_2__ {scalar_t__ seqno; } ;
struct intel_engine_cs {TYPE_1__ hangcheck; } ;
typedef  enum intel_engine_hangcheck_action { ____Placeholder_intel_engine_hangcheck_action } intel_engine_hangcheck_action ;

/* Variables and functions */
 int ENGINE_ACTIVE_SEQNO ; 
 int ENGINE_IDLE ; 
 int engine_stuck (struct intel_engine_cs*,int /*<<< orphan*/ ) ; 
 scalar_t__ intel_engine_is_idle (struct intel_engine_cs*) ; 

__attribute__((used)) static enum intel_engine_hangcheck_action
hangcheck_get_action(struct intel_engine_cs *engine,
		     const struct intel_engine_hangcheck *hc)
{
	if (engine->hangcheck.seqno != hc->seqno)
		return ENGINE_ACTIVE_SEQNO;

	if (intel_engine_is_idle(engine))
		return ENGINE_IDLE;

	return engine_stuck(engine, hc->acthd);
}
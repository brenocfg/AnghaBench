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
typedef  scalar_t__ u64 ;
struct TYPE_2__ {scalar_t__ acthd; int /*<<< orphan*/  instdone; } ;
struct intel_engine_cs {TYPE_1__ hangcheck; } ;
typedef  enum intel_engine_hangcheck_action { ____Placeholder_intel_engine_hangcheck_action } intel_engine_hangcheck_action ;

/* Variables and functions */
 int ENGINE_ACTIVE_HEAD ; 
 int ENGINE_ACTIVE_SUBUNITS ; 
 int ENGINE_DEAD ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  subunits_stuck (struct intel_engine_cs*) ; 

__attribute__((used)) static enum intel_engine_hangcheck_action
head_stuck(struct intel_engine_cs *engine, u64 acthd)
{
	if (acthd != engine->hangcheck.acthd) {

		/* Clear subunit states on head movement */
		memset(&engine->hangcheck.instdone, 0,
		       sizeof(engine->hangcheck.instdone));

		return ENGINE_ACTIVE_HEAD;
	}

	if (!subunits_stuck(engine))
		return ENGINE_ACTIVE_SUBUNITS;

	return ENGINE_DEAD;
}
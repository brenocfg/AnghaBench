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
struct TYPE_2__ {int /*<<< orphan*/  (* prepare ) (struct intel_engine_cs*) ;} ;
struct intel_engine_cs {TYPE_1__ reset; int /*<<< orphan*/  uncore; } ;

/* Variables and functions */
 int /*<<< orphan*/  FORCEWAKE_ALL ; 
 int /*<<< orphan*/  intel_uncore_forcewake_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct intel_engine_cs*) ; 

__attribute__((used)) static void reset_prepare_engine(struct intel_engine_cs *engine)
{
	/*
	 * During the reset sequence, we must prevent the engine from
	 * entering RC6. As the context state is undefined until we restart
	 * the engine, if it does enter RC6 during the reset, the state
	 * written to the powercontext is undefined and so we may lose
	 * GPU state upon resume, i.e. fail to restart after a reset.
	 */
	intel_uncore_forcewake_get(engine->uncore, FORCEWAKE_ALL);
	engine->reset.prepare(engine);
}
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
struct TYPE_2__ {int /*<<< orphan*/  (* finish ) (struct intel_engine_cs*) ;} ;
struct intel_engine_cs {int /*<<< orphan*/  uncore; TYPE_1__ reset; } ;

/* Variables and functions */
 int /*<<< orphan*/  FORCEWAKE_ALL ; 
 int /*<<< orphan*/  intel_engine_signal_breadcrumbs (struct intel_engine_cs*) ; 
 int /*<<< orphan*/  intel_uncore_forcewake_put (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct intel_engine_cs*) ; 

__attribute__((used)) static void reset_finish_engine(struct intel_engine_cs *engine)
{
	engine->reset.finish(engine);
	intel_uncore_forcewake_put(engine->uncore, FORCEWAKE_ALL);

	intel_engine_signal_breadcrumbs(engine);
}
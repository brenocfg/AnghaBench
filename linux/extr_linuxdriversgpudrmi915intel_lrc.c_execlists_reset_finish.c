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
struct TYPE_2__ {int /*<<< orphan*/  rb_root; } ;
struct intel_engine_execlists {int /*<<< orphan*/  tasklet; TYPE_1__ queue; } ;
struct intel_engine_cs {int /*<<< orphan*/  name; struct intel_engine_execlists execlists; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RB_EMPTY_ROOT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __tasklet_enable_sync_once (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void execlists_reset_finish(struct intel_engine_cs *engine)
{
	struct intel_engine_execlists * const execlists = &engine->execlists;

	/* After a GPU reset, we may have requests to replay */
	if (!RB_EMPTY_ROOT(&execlists->queue.rb_root))
		tasklet_schedule(&execlists->tasklet);

	/*
	 * Flush the tasklet while we still have the forcewake to be sure
	 * that it is not allowed to sleep before we restart and reload a
	 * context.
	 *
	 * As before (with execlists_reset_prepare) we rely on the caller
	 * serialising multiple attempts to reset so that we know that we
	 * are the only one manipulating tasklet state.
	 */
	__tasklet_enable_sync_once(&execlists->tasklet);

	GEM_TRACE("%s\n", engine->name);
}
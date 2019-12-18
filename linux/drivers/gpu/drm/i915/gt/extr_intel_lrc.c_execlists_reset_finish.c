#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  count; int /*<<< orphan*/  data; int /*<<< orphan*/  (* func ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  rb_root; } ;
struct intel_engine_execlists {TYPE_2__ tasklet; TYPE_1__ queue; } ;
struct intel_engine_cs {int /*<<< orphan*/  name; struct intel_engine_execlists execlists; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int /*<<< orphan*/  GEM_TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RB_EMPTY_ROOT (int /*<<< orphan*/ *) ; 
 scalar_t__ __tasklet_enable (TYPE_2__*) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reset_in_progress (struct intel_engine_execlists* const) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tasklet_hi_schedule (TYPE_2__*) ; 

__attribute__((used)) static void execlists_reset_finish(struct intel_engine_cs *engine)
{
	struct intel_engine_execlists * const execlists = &engine->execlists;

	/*
	 * After a GPU reset, we may have requests to replay. Do so now while
	 * we still have the forcewake to be sure that the GPU is not allowed
	 * to sleep before we restart and reload a context.
	 */
	GEM_BUG_ON(!reset_in_progress(execlists));
	if (!RB_EMPTY_ROOT(&execlists->queue.rb_root))
		execlists->tasklet.func(execlists->tasklet.data);

	if (__tasklet_enable(&execlists->tasklet))
		/* And kick in case we missed a new request submission. */
		tasklet_hi_schedule(&execlists->tasklet);
	GEM_TRACE("%s: depth->%d\n", engine->name,
		  atomic_read(&execlists->tasklet.count));
}
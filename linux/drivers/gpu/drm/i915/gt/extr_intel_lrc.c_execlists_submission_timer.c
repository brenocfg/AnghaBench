#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct timer_list {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  tasklet; } ;
struct intel_engine_cs {TYPE_1__ execlists; } ;
struct TYPE_4__ {int /*<<< orphan*/  timer; } ;

/* Variables and functions */
 struct intel_engine_cs* engine ; 
 TYPE_2__ execlists ; 
 struct intel_engine_cs* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tasklet_hi_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void execlists_submission_timer(struct timer_list *timer)
{
	struct intel_engine_cs *engine =
		from_timer(engine, timer, execlists.timer);

	/* Kick the tasklet for some interrupt coalescing and reset handling */
	tasklet_hi_schedule(&engine->execlists.tasklet);
}
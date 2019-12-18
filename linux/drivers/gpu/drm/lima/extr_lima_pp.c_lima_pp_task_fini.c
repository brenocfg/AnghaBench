#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct lima_sched_pipe {int num_processor; scalar_t__* processor; scalar_t__ bcast_processor; } ;

/* Variables and functions */
 int /*<<< orphan*/  lima_pp_soft_reset_async (scalar_t__) ; 

__attribute__((used)) static void lima_pp_task_fini(struct lima_sched_pipe *pipe)
{
	if (pipe->bcast_processor)
		lima_pp_soft_reset_async(pipe->bcast_processor);
	else {
		int i;

		for (i = 0; i < pipe->num_processor; i++)
			lima_pp_soft_reset_async(pipe->processor[i]);
	}
}
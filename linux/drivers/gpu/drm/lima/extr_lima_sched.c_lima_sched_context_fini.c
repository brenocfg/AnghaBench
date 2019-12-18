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
struct lima_sched_pipe {int dummy; } ;
struct lima_sched_context {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_sched_entity_fini (int /*<<< orphan*/ *) ; 

void lima_sched_context_fini(struct lima_sched_pipe *pipe,
			     struct lima_sched_context *context)
{
	drm_sched_entity_fini(&context->base);
}
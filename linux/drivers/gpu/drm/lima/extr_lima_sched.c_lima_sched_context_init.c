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
struct TYPE_2__ {struct drm_sched_rq* sched_rq; } ;
struct lima_sched_pipe {TYPE_1__ base; } ;
struct lima_sched_context {int /*<<< orphan*/  base; } ;
struct drm_sched_rq {int dummy; } ;
typedef  int /*<<< orphan*/  atomic_t ;

/* Variables and functions */
 int DRM_SCHED_PRIORITY_NORMAL ; 
 int drm_sched_entity_init (int /*<<< orphan*/ *,struct drm_sched_rq**,int,int /*<<< orphan*/ *) ; 

int lima_sched_context_init(struct lima_sched_pipe *pipe,
			    struct lima_sched_context *context,
			    atomic_t *guilty)
{
	struct drm_sched_rq *rq = pipe->base.sched_rq + DRM_SCHED_PRIORITY_NORMAL;

	return drm_sched_entity_init(&context->base, &rq, 1, guilty);
}
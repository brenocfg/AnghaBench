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
struct drm_sched_rq {TYPE_1__* sched; } ;
typedef  enum drm_sched_priority { ____Placeholder_drm_sched_priority } drm_sched_priority ;
struct TYPE_2__ {struct drm_sched_rq* sched_rq; } ;

/* Variables and functions */

__attribute__((used)) static void drm_sched_entity_set_rq_priority(struct drm_sched_rq **rq,
					     enum drm_sched_priority priority)
{
	*rq = &(*rq)->sched->sched_rq[priority];
}
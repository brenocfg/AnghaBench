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
struct drm_sched_entity {int /*<<< orphan*/  job_queue; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rmb () ; 
 scalar_t__ spsc_queue_count (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool drm_sched_entity_is_idle(struct drm_sched_entity *entity)
{
	rmb(); /* for list_empty to work without lock */

	if (list_empty(&entity->list) ||
	    spsc_queue_count(&entity->job_queue) == 0)
		return true;

	return false;
}
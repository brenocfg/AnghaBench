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
struct drm_sched_entity {int /*<<< orphan*/  dependency; int /*<<< orphan*/  job_queue; } ;

/* Variables and functions */
 scalar_t__ READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * spsc_queue_peek (int /*<<< orphan*/ *) ; 

bool drm_sched_entity_is_ready(struct drm_sched_entity *entity)
{
	if (spsc_queue_peek(&entity->job_queue) == NULL)
		return false;

	if (READ_ONCE(entity->dependency))
		return false;

	return true;
}
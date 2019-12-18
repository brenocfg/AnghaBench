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
struct drm_sched_entity {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_WAIT_SCHED_ENTITY_Q_EMPTY ; 
 int /*<<< orphan*/  drm_sched_entity_fini (struct drm_sched_entity*) ; 
 int /*<<< orphan*/  drm_sched_entity_flush (struct drm_sched_entity*,int /*<<< orphan*/ ) ; 

void drm_sched_entity_destroy(struct drm_sched_entity *entity)
{
	drm_sched_entity_flush(entity, MAX_WAIT_SCHED_ENTITY_Q_EMPTY);
	drm_sched_entity_fini(entity);
}
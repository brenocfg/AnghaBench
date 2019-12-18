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
struct drm_writeback_job {int /*<<< orphan*/  list_entry; } ;
struct drm_writeback_connector {int /*<<< orphan*/  job_lock; int /*<<< orphan*/  job_queue; } ;
struct drm_connector_state {struct drm_writeback_job* writeback_job; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void drm_writeback_queue_job(struct drm_writeback_connector *wb_connector,
			     struct drm_connector_state *conn_state)
{
	struct drm_writeback_job *job;
	unsigned long flags;

	job = conn_state->writeback_job;
	conn_state->writeback_job = NULL;

	spin_lock_irqsave(&wb_connector->job_lock, flags);
	list_add_tail(&job->list_entry, &wb_connector->job_queue);
	spin_unlock_irqrestore(&wb_connector->job_lock, flags);
}
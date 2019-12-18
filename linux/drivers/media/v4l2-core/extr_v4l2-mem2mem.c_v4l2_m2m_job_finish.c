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
struct v4l2_m2m_dev {int /*<<< orphan*/  job_work; int /*<<< orphan*/  job_spinlock; struct v4l2_m2m_ctx* curr_ctx; } ;
struct v4l2_m2m_ctx {int job_flags; int /*<<< orphan*/  finished; int /*<<< orphan*/  queue; } ;

/* Variables and functions */
 int TRANS_QUEUED ; 
 int TRANS_RUNNING ; 
 int /*<<< orphan*/  __v4l2_m2m_try_queue (struct v4l2_m2m_dev*,struct v4l2_m2m_ctx*) ; 
 int /*<<< orphan*/  dprintk (char*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

void v4l2_m2m_job_finish(struct v4l2_m2m_dev *m2m_dev,
			 struct v4l2_m2m_ctx *m2m_ctx)
{
	unsigned long flags;

	spin_lock_irqsave(&m2m_dev->job_spinlock, flags);
	if (!m2m_dev->curr_ctx || m2m_dev->curr_ctx != m2m_ctx) {
		spin_unlock_irqrestore(&m2m_dev->job_spinlock, flags);
		dprintk("Called by an instance not currently running\n");
		return;
	}

	list_del(&m2m_dev->curr_ctx->queue);
	m2m_dev->curr_ctx->job_flags &= ~(TRANS_QUEUED | TRANS_RUNNING);
	wake_up(&m2m_dev->curr_ctx->finished);
	m2m_dev->curr_ctx = NULL;

	spin_unlock_irqrestore(&m2m_dev->job_spinlock, flags);

	/* This instance might have more buffers ready, but since we do not
	 * allow more than one job on the job_queue per instance, each has
	 * to be scheduled separately after the previous one finishes. */
	__v4l2_m2m_try_queue(m2m_dev, m2m_ctx);

	/* We might be running in atomic context,
	 * but the job must be run in non-atomic context.
	 */
	schedule_work(&m2m_dev->job_work);
}
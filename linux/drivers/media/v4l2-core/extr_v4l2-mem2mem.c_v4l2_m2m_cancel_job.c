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
struct v4l2_m2m_dev {int /*<<< orphan*/  job_spinlock; TYPE_1__* m2m_ops; } ;
struct v4l2_m2m_ctx {int job_flags; int /*<<< orphan*/  queue; int /*<<< orphan*/  finished; int /*<<< orphan*/  priv; struct v4l2_m2m_dev* m2m_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* job_abort ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int TRANS_ABORT ; 
 int TRANS_QUEUED ; 
 int TRANS_RUNNING ; 
 int /*<<< orphan*/  dprintk (char*,struct v4l2_m2m_ctx*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void v4l2_m2m_cancel_job(struct v4l2_m2m_ctx *m2m_ctx)
{
	struct v4l2_m2m_dev *m2m_dev;
	unsigned long flags;

	m2m_dev = m2m_ctx->m2m_dev;
	spin_lock_irqsave(&m2m_dev->job_spinlock, flags);

	m2m_ctx->job_flags |= TRANS_ABORT;
	if (m2m_ctx->job_flags & TRANS_RUNNING) {
		spin_unlock_irqrestore(&m2m_dev->job_spinlock, flags);
		if (m2m_dev->m2m_ops->job_abort)
			m2m_dev->m2m_ops->job_abort(m2m_ctx->priv);
		dprintk("m2m_ctx %p running, will wait to complete\n", m2m_ctx);
		wait_event(m2m_ctx->finished,
				!(m2m_ctx->job_flags & TRANS_RUNNING));
	} else if (m2m_ctx->job_flags & TRANS_QUEUED) {
		list_del(&m2m_ctx->queue);
		m2m_ctx->job_flags &= ~(TRANS_QUEUED | TRANS_RUNNING);
		spin_unlock_irqrestore(&m2m_dev->job_spinlock, flags);
		dprintk("m2m_ctx: %p had been on queue and was removed\n",
			m2m_ctx);
	} else {
		/* Do nothing, was not on queue/running */
		spin_unlock_irqrestore(&m2m_dev->job_spinlock, flags);
	}
}
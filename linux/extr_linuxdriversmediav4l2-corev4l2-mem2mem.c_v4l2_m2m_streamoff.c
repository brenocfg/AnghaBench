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
struct v4l2_m2m_queue_ctx {int /*<<< orphan*/  rdy_spinlock; scalar_t__ num_rdy; int /*<<< orphan*/  rdy_queue; int /*<<< orphan*/  q; } ;
struct v4l2_m2m_dev {int /*<<< orphan*/  job_spinlock; struct v4l2_m2m_ctx* curr_ctx; } ;
struct v4l2_m2m_ctx {int job_flags; int /*<<< orphan*/  finished; int /*<<< orphan*/  queue; struct v4l2_m2m_dev* m2m_dev; } ;
struct file {int dummy; } ;
typedef  enum v4l2_buf_type { ____Placeholder_v4l2_buf_type } v4l2_buf_type ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int TRANS_QUEUED ; 
 struct v4l2_m2m_queue_ctx* get_queue_ctx (struct v4l2_m2m_ctx*,int) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  v4l2_m2m_cancel_job (struct v4l2_m2m_ctx*) ; 
 int vb2_streamoff (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

int v4l2_m2m_streamoff(struct file *file, struct v4l2_m2m_ctx *m2m_ctx,
		       enum v4l2_buf_type type)
{
	struct v4l2_m2m_dev *m2m_dev;
	struct v4l2_m2m_queue_ctx *q_ctx;
	unsigned long flags_job, flags;
	int ret;

	/* wait until the current context is dequeued from job_queue */
	v4l2_m2m_cancel_job(m2m_ctx);

	q_ctx = get_queue_ctx(m2m_ctx, type);
	ret = vb2_streamoff(&q_ctx->q, type);
	if (ret)
		return ret;

	m2m_dev = m2m_ctx->m2m_dev;
	spin_lock_irqsave(&m2m_dev->job_spinlock, flags_job);
	/* We should not be scheduled anymore, since we're dropping a queue. */
	if (m2m_ctx->job_flags & TRANS_QUEUED)
		list_del(&m2m_ctx->queue);
	m2m_ctx->job_flags = 0;

	spin_lock_irqsave(&q_ctx->rdy_spinlock, flags);
	/* Drop queue, since streamoff returns device to the same state as after
	 * calling reqbufs. */
	INIT_LIST_HEAD(&q_ctx->rdy_queue);
	q_ctx->num_rdy = 0;
	spin_unlock_irqrestore(&q_ctx->rdy_spinlock, flags);

	if (m2m_dev->curr_ctx == m2m_ctx) {
		m2m_dev->curr_ctx = NULL;
		wake_up(&m2m_ctx->finished);
	}
	spin_unlock_irqrestore(&m2m_dev->job_spinlock, flags_job);

	return 0;
}
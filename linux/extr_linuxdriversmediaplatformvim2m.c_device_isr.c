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
struct vim2m_dev {int /*<<< orphan*/  m2m_dev; int /*<<< orphan*/  irqlock; } ;
struct TYPE_2__ {int /*<<< orphan*/  m2m_ctx; } ;
struct vim2m_ctx {scalar_t__ num_processed; scalar_t__ translen; TYPE_1__ fh; int /*<<< orphan*/  dev; scalar_t__ aborting; } ;
struct vb2_v4l2_buffer {int dummy; } ;
struct timer_list {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VB2_BUF_STATE_DONE ; 
 int /*<<< orphan*/  device_run (struct vim2m_ctx*) ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,char*) ; 
 struct vim2m_dev* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  timer ; 
 int /*<<< orphan*/  v4l2_m2m_buf_done (struct vb2_v4l2_buffer*,int /*<<< orphan*/ ) ; 
 struct vb2_v4l2_buffer* v4l2_m2m_dst_buf_remove (int /*<<< orphan*/ ) ; 
 struct vim2m_ctx* v4l2_m2m_get_curr_priv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_m2m_job_finish (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct vb2_v4l2_buffer* v4l2_m2m_src_buf_remove (int /*<<< orphan*/ ) ; 
 struct vim2m_dev* vim2m_dev ; 

__attribute__((used)) static void device_isr(struct timer_list *t)
{
	struct vim2m_dev *vim2m_dev = from_timer(vim2m_dev, t, timer);
	struct vim2m_ctx *curr_ctx;
	struct vb2_v4l2_buffer *src_vb, *dst_vb;
	unsigned long flags;

	curr_ctx = v4l2_m2m_get_curr_priv(vim2m_dev->m2m_dev);

	if (NULL == curr_ctx) {
		pr_err("Instance released before the end of transaction\n");
		return;
	}

	src_vb = v4l2_m2m_src_buf_remove(curr_ctx->fh.m2m_ctx);
	dst_vb = v4l2_m2m_dst_buf_remove(curr_ctx->fh.m2m_ctx);

	curr_ctx->num_processed++;

	spin_lock_irqsave(&vim2m_dev->irqlock, flags);
	v4l2_m2m_buf_done(src_vb, VB2_BUF_STATE_DONE);
	v4l2_m2m_buf_done(dst_vb, VB2_BUF_STATE_DONE);
	spin_unlock_irqrestore(&vim2m_dev->irqlock, flags);

	if (curr_ctx->num_processed == curr_ctx->translen
	    || curr_ctx->aborting) {
		dprintk(curr_ctx->dev, "Finishing transaction\n");
		curr_ctx->num_processed = 0;
		v4l2_m2m_job_finish(vim2m_dev->m2m_dev, curr_ctx->fh.m2m_ctx);
	} else {
		device_run(curr_ctx);
	}
}
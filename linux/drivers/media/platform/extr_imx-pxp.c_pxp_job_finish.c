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
struct vb2_v4l2_buffer {int dummy; } ;
struct pxp_dev {int /*<<< orphan*/  m2m_dev; int /*<<< orphan*/  irqlock; } ;
struct TYPE_2__ {int /*<<< orphan*/  m2m_ctx; } ;
struct pxp_ctx {TYPE_1__ fh; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  VB2_BUF_STATE_DONE ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  v4l2_m2m_buf_done (struct vb2_v4l2_buffer*,int /*<<< orphan*/ ) ; 
 struct vb2_v4l2_buffer* v4l2_m2m_dst_buf_remove (int /*<<< orphan*/ ) ; 
 struct pxp_ctx* v4l2_m2m_get_curr_priv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_m2m_job_finish (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct vb2_v4l2_buffer* v4l2_m2m_src_buf_remove (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pxp_job_finish(struct pxp_dev *dev)
{
	struct pxp_ctx *curr_ctx;
	struct vb2_v4l2_buffer *src_vb, *dst_vb;
	unsigned long flags;

	curr_ctx = v4l2_m2m_get_curr_priv(dev->m2m_dev);

	if (curr_ctx == NULL) {
		pr_err("Instance released before the end of transaction\n");
		return;
	}

	src_vb = v4l2_m2m_src_buf_remove(curr_ctx->fh.m2m_ctx);
	dst_vb = v4l2_m2m_dst_buf_remove(curr_ctx->fh.m2m_ctx);

	spin_lock_irqsave(&dev->irqlock, flags);
	v4l2_m2m_buf_done(src_vb, VB2_BUF_STATE_DONE);
	v4l2_m2m_buf_done(dst_vb, VB2_BUF_STATE_DONE);
	spin_unlock_irqrestore(&dev->irqlock, flags);

	dprintk(curr_ctx->dev, "Finishing transaction\n");
	v4l2_m2m_job_finish(dev->m2m_dev, curr_ctx->fh.m2m_ctx);
}
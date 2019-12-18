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
struct vpe_dev {int /*<<< orphan*/  lock; } ;
struct vpe_ctx {int /*<<< orphan*/ ** src_vbs; struct vpe_dev* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  VB2_BUF_STATE_DONE ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  v4l2_m2m_buf_done (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void free_vbs(struct vpe_ctx *ctx)
{
	struct vpe_dev *dev = ctx->dev;
	unsigned long flags;

	if (ctx->src_vbs[2] == NULL)
		return;

	spin_lock_irqsave(&dev->lock, flags);
	if (ctx->src_vbs[2]) {
		v4l2_m2m_buf_done(ctx->src_vbs[2], VB2_BUF_STATE_DONE);
		if (ctx->src_vbs[1] && (ctx->src_vbs[1] != ctx->src_vbs[2]))
			v4l2_m2m_buf_done(ctx->src_vbs[1], VB2_BUF_STATE_DONE);
		ctx->src_vbs[2] = NULL;
		ctx->src_vbs[1] = NULL;
	}
	spin_unlock_irqrestore(&dev->lock, flags);
}
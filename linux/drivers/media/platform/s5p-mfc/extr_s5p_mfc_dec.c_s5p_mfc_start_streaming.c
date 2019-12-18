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
struct vb2_queue {int /*<<< orphan*/  drv_priv; } ;
struct s5p_mfc_dev {int /*<<< orphan*/  mfc_ops; } ;
struct s5p_mfc_ctx {scalar_t__ state; int /*<<< orphan*/  ctrl_handler; struct s5p_mfc_dev* dev; } ;

/* Variables and functions */
 scalar_t__ MFCINST_FINISHED ; 
 scalar_t__ MFCINST_FINISHING ; 
 scalar_t__ MFCINST_RUNNING ; 
 struct s5p_mfc_ctx* fh_to_ctx (int /*<<< orphan*/ ) ; 
 scalar_t__ s5p_mfc_ctx_ready (struct s5p_mfc_ctx*) ; 
 int /*<<< orphan*/  s5p_mfc_hw_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct s5p_mfc_dev*) ; 
 int /*<<< orphan*/  set_work_bit_irqsave (struct s5p_mfc_ctx*) ; 
 int /*<<< orphan*/  try_run ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_setup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int s5p_mfc_start_streaming(struct vb2_queue *q, unsigned int count)
{
	struct s5p_mfc_ctx *ctx = fh_to_ctx(q->drv_priv);
	struct s5p_mfc_dev *dev = ctx->dev;

	v4l2_ctrl_handler_setup(&ctx->ctrl_handler);
	if (ctx->state == MFCINST_FINISHING ||
		ctx->state == MFCINST_FINISHED)
		ctx->state = MFCINST_RUNNING;
	/* If context is ready then dev = work->data;schedule it to run */
	if (s5p_mfc_ctx_ready(ctx))
		set_work_bit_irqsave(ctx);
	s5p_mfc_hw_call(dev->mfc_ops, try_run, dev);
	return 0;
}
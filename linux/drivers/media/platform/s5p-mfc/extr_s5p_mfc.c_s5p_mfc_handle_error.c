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
struct s5p_mfc_dev {int /*<<< orphan*/  mfc_ops; int /*<<< orphan*/  hw_lock; } ;
struct s5p_mfc_ctx {int state; int /*<<< orphan*/  vq_src; int /*<<< orphan*/  src_queue; int /*<<< orphan*/  vq_dst; int /*<<< orphan*/  dst_queue; } ;

/* Variables and functions */
 void* MFCINST_ERROR ; 
#define  MFCINST_FINISHED 133 
#define  MFCINST_FINISHING 132 
#define  MFCINST_RES_CHANGE_END 131 
#define  MFCINST_RES_CHANGE_FLUSH 130 
#define  MFCINST_RES_CHANGE_INIT 129 
#define  MFCINST_RUNNING 128 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  clear_int_flags ; 
 int /*<<< orphan*/  clear_work_bit (struct s5p_mfc_ctx*) ; 
 int /*<<< orphan*/  mfc_err (char*,unsigned int) ; 
 int /*<<< orphan*/  s5p_mfc_cleanup_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  s5p_mfc_clock_off () ; 
 int /*<<< orphan*/  s5p_mfc_hw_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct s5p_mfc_dev*) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_ctx (struct s5p_mfc_ctx*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  wake_up_dev (struct s5p_mfc_dev*,unsigned int,unsigned int) ; 

__attribute__((used)) static void s5p_mfc_handle_error(struct s5p_mfc_dev *dev,
		struct s5p_mfc_ctx *ctx, unsigned int reason, unsigned int err)
{
	mfc_err("Interrupt Error: %08x\n", err);

	if (ctx) {
		/* Error recovery is dependent on the state of context */
		switch (ctx->state) {
		case MFCINST_RES_CHANGE_INIT:
		case MFCINST_RES_CHANGE_FLUSH:
		case MFCINST_RES_CHANGE_END:
		case MFCINST_FINISHING:
		case MFCINST_FINISHED:
		case MFCINST_RUNNING:
			/* It is highly probable that an error occurred
			 * while decoding a frame */
			clear_work_bit(ctx);
			ctx->state = MFCINST_ERROR;
			/* Mark all dst buffers as having an error */
			s5p_mfc_cleanup_queue(&ctx->dst_queue, &ctx->vq_dst);
			/* Mark all src buffers as having an error */
			s5p_mfc_cleanup_queue(&ctx->src_queue, &ctx->vq_src);
			wake_up_ctx(ctx, reason, err);
			break;
		default:
			clear_work_bit(ctx);
			ctx->state = MFCINST_ERROR;
			wake_up_ctx(ctx, reason, err);
			break;
		}
	}
	WARN_ON(test_and_clear_bit(0, &dev->hw_lock) == 0);
	s5p_mfc_hw_call(dev->mfc_ops, clear_int_flags, dev);
	s5p_mfc_clock_off();
	wake_up_dev(dev, reason, err);
}
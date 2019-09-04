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
struct s5p_mfc_dev {size_t curr_ctx; void* warn_start; int /*<<< orphan*/  irqlock; int /*<<< orphan*/  mfc_ops; int /*<<< orphan*/  hw_lock; int /*<<< orphan*/  enter_suspend; struct s5p_mfc_ctx** ctx; int /*<<< orphan*/  watchdog_cnt; } ;
struct s5p_mfc_ctx {unsigned int int_type; unsigned int int_err; int int_cond; int /*<<< orphan*/  queue; int /*<<< orphan*/  state; void* inst_no; int /*<<< orphan*/  ref_queue; TYPE_1__* c_ops; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* post_frame_start ) (struct s5p_mfc_ctx*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  MFCINST_FINISHING ; 
 int /*<<< orphan*/  MFCINST_FREE ; 
 int /*<<< orphan*/  MFCINST_GOT_INST ; 
 int /*<<< orphan*/  MFCINST_RUNNING ; 
 void* MFC_NO_INSTANCE_SET ; 
 unsigned int S5P_FIMV_ERR_INCOMPLETE_FRAME ; 
 unsigned int S5P_FIMV_ERR_NO_VALID_SEQ_HDR ; 
 unsigned int S5P_FIMV_ERR_TIMEOUT ; 
#define  S5P_MFC_R2H_CMD_CLOSE_INSTANCE_RET 141 
#define  S5P_MFC_R2H_CMD_COMPLETE_SEQ_RET 140 
#define  S5P_MFC_R2H_CMD_DPB_FLUSH_RET 139 
#define  S5P_MFC_R2H_CMD_ERR_RET 138 
#define  S5P_MFC_R2H_CMD_FIELD_DONE_RET 137 
#define  S5P_MFC_R2H_CMD_FRAME_DONE_RET 136 
#define  S5P_MFC_R2H_CMD_FW_STATUS_RET 135 
#define  S5P_MFC_R2H_CMD_INIT_BUFFERS_RET 134 
#define  S5P_MFC_R2H_CMD_OPEN_INSTANCE_RET 133 
#define  S5P_MFC_R2H_CMD_SEQ_DONE_RET 132 
#define  S5P_MFC_R2H_CMD_SLEEP_RET 131 
#define  S5P_MFC_R2H_CMD_SLICE_DONE_RET 130 
#define  S5P_MFC_R2H_CMD_SYS_INIT_RET 129 
#define  S5P_MFC_R2H_CMD_WAKEUP_RET 128 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_int_flags ; 
 int /*<<< orphan*/  clear_work_bit (struct s5p_mfc_ctx*) ; 
 int /*<<< orphan*/  err_dec ; 
 int /*<<< orphan*/  get_inst_no ; 
 int /*<<< orphan*/  get_int_err ; 
 int /*<<< orphan*/  get_int_reason ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mfc_debug (int,char*,...) ; 
 int /*<<< orphan*/  mfc_debug_enter () ; 
 int /*<<< orphan*/  mfc_debug_leave () ; 
 int /*<<< orphan*/  mfc_err (char*) ; 
 int /*<<< orphan*/  s5p_mfc_clock_off () ; 
 int /*<<< orphan*/  s5p_mfc_handle_error (struct s5p_mfc_dev*,struct s5p_mfc_ctx*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  s5p_mfc_handle_frame (struct s5p_mfc_ctx*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  s5p_mfc_handle_init_buffers (struct s5p_mfc_ctx*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  s5p_mfc_handle_seq_done (struct s5p_mfc_ctx*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  s5p_mfc_handle_stream_complete (struct s5p_mfc_ctx*) ; 
 void* s5p_mfc_hw_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct s5p_mfc_ctx*) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  try_run ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_ctx (struct s5p_mfc_ctx*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  wake_up_dev (struct s5p_mfc_dev*,unsigned int,unsigned int) ; 

__attribute__((used)) static irqreturn_t s5p_mfc_irq(int irq, void *priv)
{
	struct s5p_mfc_dev *dev = priv;
	struct s5p_mfc_ctx *ctx;
	unsigned int reason;
	unsigned int err;

	mfc_debug_enter();
	/* Reset the timeout watchdog */
	atomic_set(&dev->watchdog_cnt, 0);
	spin_lock(&dev->irqlock);
	ctx = dev->ctx[dev->curr_ctx];
	/* Get the reason of interrupt and the error code */
	reason = s5p_mfc_hw_call(dev->mfc_ops, get_int_reason, dev);
	err = s5p_mfc_hw_call(dev->mfc_ops, get_int_err, dev);
	mfc_debug(1, "Int reason: %d (err: %08x)\n", reason, err);
	switch (reason) {
	case S5P_MFC_R2H_CMD_ERR_RET:
		/* An error has occurred */
		if (ctx->state == MFCINST_RUNNING &&
			(s5p_mfc_hw_call(dev->mfc_ops, err_dec, err) >=
				dev->warn_start ||
				err == S5P_FIMV_ERR_NO_VALID_SEQ_HDR ||
				err == S5P_FIMV_ERR_INCOMPLETE_FRAME ||
				err == S5P_FIMV_ERR_TIMEOUT))
			s5p_mfc_handle_frame(ctx, reason, err);
		else
			s5p_mfc_handle_error(dev, ctx, reason, err);
		clear_bit(0, &dev->enter_suspend);
		break;

	case S5P_MFC_R2H_CMD_SLICE_DONE_RET:
	case S5P_MFC_R2H_CMD_FIELD_DONE_RET:
	case S5P_MFC_R2H_CMD_FRAME_DONE_RET:
		if (ctx->c_ops->post_frame_start) {
			if (ctx->c_ops->post_frame_start(ctx))
				mfc_err("post_frame_start() failed\n");

			if (ctx->state == MFCINST_FINISHING &&
						list_empty(&ctx->ref_queue)) {
				s5p_mfc_hw_call(dev->mfc_ops, clear_int_flags, dev);
				s5p_mfc_handle_stream_complete(ctx);
				break;
			}
			s5p_mfc_hw_call(dev->mfc_ops, clear_int_flags, dev);
			WARN_ON(test_and_clear_bit(0, &dev->hw_lock) == 0);
			s5p_mfc_clock_off();
			wake_up_ctx(ctx, reason, err);
			s5p_mfc_hw_call(dev->mfc_ops, try_run, dev);
		} else {
			s5p_mfc_handle_frame(ctx, reason, err);
		}
		break;

	case S5P_MFC_R2H_CMD_SEQ_DONE_RET:
		s5p_mfc_handle_seq_done(ctx, reason, err);
		break;

	case S5P_MFC_R2H_CMD_OPEN_INSTANCE_RET:
		ctx->inst_no = s5p_mfc_hw_call(dev->mfc_ops, get_inst_no, dev);
		ctx->state = MFCINST_GOT_INST;
		goto irq_cleanup_hw;

	case S5P_MFC_R2H_CMD_CLOSE_INSTANCE_RET:
		ctx->inst_no = MFC_NO_INSTANCE_SET;
		ctx->state = MFCINST_FREE;
		goto irq_cleanup_hw;

	case S5P_MFC_R2H_CMD_SYS_INIT_RET:
	case S5P_MFC_R2H_CMD_FW_STATUS_RET:
	case S5P_MFC_R2H_CMD_SLEEP_RET:
	case S5P_MFC_R2H_CMD_WAKEUP_RET:
		if (ctx)
			clear_work_bit(ctx);
		s5p_mfc_hw_call(dev->mfc_ops, clear_int_flags, dev);
		clear_bit(0, &dev->hw_lock);
		clear_bit(0, &dev->enter_suspend);
		wake_up_dev(dev, reason, err);
		break;

	case S5P_MFC_R2H_CMD_INIT_BUFFERS_RET:
		s5p_mfc_handle_init_buffers(ctx, reason, err);
		break;

	case S5P_MFC_R2H_CMD_COMPLETE_SEQ_RET:
		s5p_mfc_hw_call(dev->mfc_ops, clear_int_flags, dev);
		ctx->int_type = reason;
		ctx->int_err = err;
		s5p_mfc_handle_stream_complete(ctx);
		break;

	case S5P_MFC_R2H_CMD_DPB_FLUSH_RET:
		ctx->state = MFCINST_RUNNING;
		goto irq_cleanup_hw;

	default:
		mfc_debug(2, "Unknown int reason\n");
		s5p_mfc_hw_call(dev->mfc_ops, clear_int_flags, dev);
	}
	spin_unlock(&dev->irqlock);
	mfc_debug_leave();
	return IRQ_HANDLED;
irq_cleanup_hw:
	s5p_mfc_hw_call(dev->mfc_ops, clear_int_flags, dev);
	ctx->int_type = reason;
	ctx->int_err = err;
	ctx->int_cond = 1;
	if (test_and_clear_bit(0, &dev->hw_lock) == 0)
		mfc_err("Failed to unlock hw\n");

	s5p_mfc_clock_off();
	clear_work_bit(ctx);
	wake_up(&ctx->queue);

	s5p_mfc_hw_call(dev->mfc_ops, try_run, dev);
	spin_unlock(&dev->irqlock);
	mfc_debug(2, "Exit via irq_cleanup_hw\n");
	return IRQ_HANDLED;
}
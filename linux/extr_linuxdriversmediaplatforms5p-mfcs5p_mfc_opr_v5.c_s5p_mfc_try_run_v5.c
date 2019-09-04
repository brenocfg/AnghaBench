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
struct s5p_mfc_dev {int /*<<< orphan*/  hw_lock; int /*<<< orphan*/  mfc_cmds; struct s5p_mfc_ctx** ctx; int /*<<< orphan*/  enter_suspend; } ;
struct s5p_mfc_ctx {scalar_t__ type; int state; int /*<<< orphan*/  capture_state; } ;

/* Variables and functions */
 unsigned int EAGAIN ; 
 scalar_t__ MFCINST_DECODER ; 
 scalar_t__ MFCINST_ENCODER ; 
#define  MFCINST_FINISHING 136 
#define  MFCINST_GOT_INST 135 
#define  MFCINST_HEAD_PARSED 134 
#define  MFCINST_INIT 133 
#define  MFCINST_RES_CHANGE_END 132 
#define  MFCINST_RES_CHANGE_FLUSH 131 
#define  MFCINST_RES_CHANGE_INIT 130 
#define  MFCINST_RETURN_INST 129 
#define  MFCINST_RUNNING 128 
 int /*<<< orphan*/  MFC_DEC_FRAME ; 
 int /*<<< orphan*/  MFC_DEC_LAST_FRAME ; 
 int /*<<< orphan*/  QUEUE_FREE ; 
 int /*<<< orphan*/  close_inst_cmd ; 
 int /*<<< orphan*/  mfc_debug (int,char*) ; 
 int /*<<< orphan*/  mfc_err (char*,...) ; 
 int /*<<< orphan*/  open_inst_cmd ; 
 int /*<<< orphan*/  s5p_mfc_clean_ctx_int_flags (struct s5p_mfc_ctx*) ; 
 int /*<<< orphan*/  s5p_mfc_clock_off () ; 
 int /*<<< orphan*/  s5p_mfc_clock_on () ; 
 int s5p_mfc_get_new_ctx (struct s5p_mfc_dev*) ; 
 unsigned int s5p_mfc_hw_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct s5p_mfc_ctx*) ; 
 unsigned int s5p_mfc_run_dec_frame (struct s5p_mfc_ctx*,int /*<<< orphan*/ ) ; 
 unsigned int s5p_mfc_run_enc_frame (struct s5p_mfc_ctx*) ; 
 int /*<<< orphan*/  s5p_mfc_run_init_dec (struct s5p_mfc_ctx*) ; 
 unsigned int s5p_mfc_run_init_dec_buffers (struct s5p_mfc_ctx*) ; 
 int /*<<< orphan*/  s5p_mfc_run_init_enc (struct s5p_mfc_ctx*) ; 
 int /*<<< orphan*/  s5p_mfc_run_res_change (struct s5p_mfc_ctx*) ; 
 int /*<<< orphan*/  s5p_mfc_set_dec_desc_buffer (struct s5p_mfc_ctx*) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void s5p_mfc_try_run_v5(struct s5p_mfc_dev *dev)
{
	struct s5p_mfc_ctx *ctx;
	int new_ctx;
	unsigned int ret = 0;

	if (test_bit(0, &dev->enter_suspend)) {
		mfc_debug(1, "Entering suspend so do not schedule any jobs\n");
		return;
	}
	/* Check whether hardware is not running */
	if (test_and_set_bit(0, &dev->hw_lock) != 0) {
		/* This is perfectly ok, the scheduled ctx should wait */
		mfc_debug(1, "Couldn't lock HW\n");
		return;
	}
	/* Choose the context to run */
	new_ctx = s5p_mfc_get_new_ctx(dev);
	if (new_ctx < 0) {
		/* No contexts to run */
		if (test_and_clear_bit(0, &dev->hw_lock) == 0) {
			mfc_err("Failed to unlock hardware\n");
			return;
		}
		mfc_debug(1, "No ctx is scheduled to be run\n");
		return;
	}
	ctx = dev->ctx[new_ctx];
	/* Got context to run in ctx */
	/*
	 * Last frame has already been sent to MFC.
	 * Now obtaining frames from MFC buffer
	 */
	s5p_mfc_clock_on();
	s5p_mfc_clean_ctx_int_flags(ctx);

	if (ctx->type == MFCINST_DECODER) {
		s5p_mfc_set_dec_desc_buffer(ctx);
		switch (ctx->state) {
		case MFCINST_FINISHING:
			s5p_mfc_run_dec_frame(ctx, MFC_DEC_LAST_FRAME);
			break;
		case MFCINST_RUNNING:
			ret = s5p_mfc_run_dec_frame(ctx, MFC_DEC_FRAME);
			break;
		case MFCINST_INIT:
			ret = s5p_mfc_hw_call(dev->mfc_cmds, open_inst_cmd,
					ctx);
			break;
		case MFCINST_RETURN_INST:
			ret = s5p_mfc_hw_call(dev->mfc_cmds, close_inst_cmd,
					ctx);
			break;
		case MFCINST_GOT_INST:
			s5p_mfc_run_init_dec(ctx);
			break;
		case MFCINST_HEAD_PARSED:
			ret = s5p_mfc_run_init_dec_buffers(ctx);
			mfc_debug(1, "head parsed\n");
			break;
		case MFCINST_RES_CHANGE_INIT:
			s5p_mfc_run_res_change(ctx);
			break;
		case MFCINST_RES_CHANGE_FLUSH:
			s5p_mfc_run_dec_frame(ctx, MFC_DEC_FRAME);
			break;
		case MFCINST_RES_CHANGE_END:
			mfc_debug(2, "Finished remaining frames after resolution change\n");
			ctx->capture_state = QUEUE_FREE;
			mfc_debug(2, "Will re-init the codec\n");
			s5p_mfc_run_init_dec(ctx);
			break;
		default:
			ret = -EAGAIN;
		}
	} else if (ctx->type == MFCINST_ENCODER) {
		switch (ctx->state) {
		case MFCINST_FINISHING:
		case MFCINST_RUNNING:
			ret = s5p_mfc_run_enc_frame(ctx);
			break;
		case MFCINST_INIT:
			ret = s5p_mfc_hw_call(dev->mfc_cmds, open_inst_cmd,
					ctx);
			break;
		case MFCINST_RETURN_INST:
			ret = s5p_mfc_hw_call(dev->mfc_cmds, close_inst_cmd,
					ctx);
			break;
		case MFCINST_GOT_INST:
			s5p_mfc_run_init_enc(ctx);
			break;
		default:
			ret = -EAGAIN;
		}
	} else {
		mfc_err("Invalid context type: %d\n", ctx->type);
		ret = -EAGAIN;
	}

	if (ret) {
		/* Free hardware lock */
		if (test_and_clear_bit(0, &dev->hw_lock) == 0)
			mfc_err("Failed to unlock hardware\n");

		/* This is in deed imporant, as no operation has been
		 * scheduled, reduce the clock count as no one will
		 * ever do this, because no interrupt related to this try_run
		 * will ever come from hardware. */
		s5p_mfc_clock_off();
	}
}
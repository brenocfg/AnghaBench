#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct gsc_ctx* ctx; } ;
struct gsc_dev {int /*<<< orphan*/  slock; int /*<<< orphan*/  irq_queue; TYPE_1__ m2m; int /*<<< orphan*/  state; } ;
struct TYPE_5__ {int /*<<< orphan*/  addr; } ;
struct TYPE_6__ {int /*<<< orphan*/  addr; } ;
struct gsc_ctx {int state; TYPE_2__ d_frame; TYPE_3__ s_frame; struct gsc_dev* gsc_dev; } ;

/* Variables and functions */
 int GSC_CTX_ABORT ; 
 int GSC_CTX_STOP_REQ ; 
 int /*<<< orphan*/  GSC_M2M_BUF_NUM ; 
 int GSC_PARAMS ; 
 int /*<<< orphan*/  ST_M2M_PEND ; 
 scalar_t__ WARN (int,char*) ; 
 int gsc_get_bufs (struct gsc_ctx*) ; 
 int /*<<< orphan*/  gsc_hw_enable_control (struct gsc_dev*,int) ; 
 int /*<<< orphan*/  gsc_hw_set_frm_done_irq_mask (struct gsc_dev*,int) ; 
 int /*<<< orphan*/  gsc_hw_set_global_alpha (struct gsc_ctx*) ; 
 int /*<<< orphan*/  gsc_hw_set_gsc_irq_enable (struct gsc_dev*,int) ; 
 int /*<<< orphan*/  gsc_hw_set_in_image_format (struct gsc_ctx*) ; 
 int /*<<< orphan*/  gsc_hw_set_in_size (struct gsc_ctx*) ; 
 int /*<<< orphan*/  gsc_hw_set_input_addr (struct gsc_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gsc_hw_set_input_buf_masking (struct gsc_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gsc_hw_set_input_path (struct gsc_ctx*) ; 
 int /*<<< orphan*/  gsc_hw_set_mainscaler (struct gsc_ctx*) ; 
 int /*<<< orphan*/  gsc_hw_set_out_image_format (struct gsc_ctx*) ; 
 int /*<<< orphan*/  gsc_hw_set_out_size (struct gsc_ctx*) ; 
 int /*<<< orphan*/  gsc_hw_set_output_addr (struct gsc_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gsc_hw_set_output_buf_masking (struct gsc_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gsc_hw_set_output_path (struct gsc_ctx*) ; 
 int /*<<< orphan*/  gsc_hw_set_prescaler (struct gsc_ctx*) ; 
 int /*<<< orphan*/  gsc_hw_set_rotation (struct gsc_ctx*) ; 
 int /*<<< orphan*/  gsc_hw_set_sfr_update (struct gsc_ctx*) ; 
 int /*<<< orphan*/  gsc_set_prefbuf (struct gsc_dev*,TYPE_3__*) ; 
 scalar_t__ gsc_set_scaler_info (struct gsc_ctx*) ; 
 int /*<<< orphan*/  pr_debug (char*,struct gsc_ctx*,struct gsc_ctx*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void gsc_m2m_device_run(void *priv)
{
	struct gsc_ctx *ctx = priv;
	struct gsc_dev *gsc;
	unsigned long flags;
	int ret;
	bool is_set = false;

	if (WARN(!ctx, "null hardware context\n"))
		return;

	gsc = ctx->gsc_dev;
	spin_lock_irqsave(&gsc->slock, flags);

	set_bit(ST_M2M_PEND, &gsc->state);

	/* Reconfigure hardware if the context has changed. */
	if (gsc->m2m.ctx != ctx) {
		pr_debug("gsc->m2m.ctx = 0x%p, current_ctx = 0x%p",
				gsc->m2m.ctx, ctx);
		ctx->state |= GSC_PARAMS;
		gsc->m2m.ctx = ctx;
	}

	is_set = ctx->state & GSC_CTX_STOP_REQ;
	if (is_set) {
		ctx->state &= ~GSC_CTX_STOP_REQ;
		ctx->state |= GSC_CTX_ABORT;
		wake_up(&gsc->irq_queue);
		goto put_device;
	}

	ret = gsc_get_bufs(ctx);
	if (ret) {
		pr_err("Wrong address");
		goto put_device;
	}

	gsc_set_prefbuf(gsc, &ctx->s_frame);
	gsc_hw_set_input_addr(gsc, &ctx->s_frame.addr, GSC_M2M_BUF_NUM);
	gsc_hw_set_output_addr(gsc, &ctx->d_frame.addr, GSC_M2M_BUF_NUM);

	if (ctx->state & GSC_PARAMS) {
		gsc_hw_set_input_buf_masking(gsc, GSC_M2M_BUF_NUM, false);
		gsc_hw_set_output_buf_masking(gsc, GSC_M2M_BUF_NUM, false);
		gsc_hw_set_frm_done_irq_mask(gsc, false);
		gsc_hw_set_gsc_irq_enable(gsc, true);

		if (gsc_set_scaler_info(ctx)) {
			pr_err("Scaler setup error");
			goto put_device;
		}

		gsc_hw_set_input_path(ctx);
		gsc_hw_set_in_size(ctx);
		gsc_hw_set_in_image_format(ctx);

		gsc_hw_set_output_path(ctx);
		gsc_hw_set_out_size(ctx);
		gsc_hw_set_out_image_format(ctx);

		gsc_hw_set_prescaler(ctx);
		gsc_hw_set_mainscaler(ctx);
		gsc_hw_set_rotation(ctx);
		gsc_hw_set_global_alpha(ctx);
	}

	/* update shadow registers */
	gsc_hw_set_sfr_update(ctx);

	ctx->state &= ~GSC_PARAMS;
	gsc_hw_enable_control(gsc, true);

	spin_unlock_irqrestore(&gsc->slock, flags);
	return;

put_device:
	ctx->state &= ~GSC_PARAMS;
	spin_unlock_irqrestore(&gsc->slock, flags);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct file {int /*<<< orphan*/  private_data; } ;
struct delta_dev {int /*<<< orphan*/  lock; int /*<<< orphan*/  dev; scalar_t__ clk_flash_promip; scalar_t__ clk_st231; } ;
struct delta_dec {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  m2m_ctx; } ;
struct delta_ctx {int /*<<< orphan*/  name; TYPE_1__ fh; struct delta_dec* dec; struct delta_dev* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  call_dec_op (struct delta_dec const*,int /*<<< orphan*/ ,struct delta_ctx*) ; 
 int /*<<< orphan*/  clk_disable_unprepare (scalar_t__) ; 
 int /*<<< orphan*/  close ; 
 int /*<<< orphan*/  delta_trace_summary (struct delta_ctx*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct delta_ctx*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct delta_ctx* to_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_fh_del (TYPE_1__*) ; 
 int /*<<< orphan*/  v4l2_fh_exit (TYPE_1__*) ; 
 int /*<<< orphan*/  v4l2_m2m_ctx_release (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int delta_release(struct file *file)
{
	struct delta_ctx *ctx = to_ctx(file->private_data);
	struct delta_dev *delta = ctx->dev;
	const struct delta_dec *dec = ctx->dec;

	mutex_lock(&delta->lock);

	/* close decoder */
	call_dec_op(dec, close, ctx);

	/*
	 * trace a summary of instance
	 * before closing (debug purpose)
	 */
	delta_trace_summary(ctx);

	v4l2_m2m_ctx_release(ctx->fh.m2m_ctx);

	v4l2_fh_del(&ctx->fh);
	v4l2_fh_exit(&ctx->fh);

	/* disable ST231 clocks */
	if (delta->clk_st231)
		clk_disable_unprepare(delta->clk_st231);

	/* disable FLASH_PROMIP clock */
	if (delta->clk_flash_promip)
		clk_disable_unprepare(delta->clk_flash_promip);

	dev_dbg(delta->dev, "%s decoder instance released\n", ctx->name);

	kfree(ctx);

	mutex_unlock(&delta->lock);
	return 0;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct file {TYPE_1__* private_data; } ;
struct delta_dev {int instance_id; int /*<<< orphan*/  lock; int /*<<< orphan*/  dev; scalar_t__ clk_flash_promip; scalar_t__ clk_st231; int /*<<< orphan*/  m2m_dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  m2m_ctx; } ;
struct delta_ctx {TYPE_1__ fh; int /*<<< orphan*/  name; int /*<<< orphan*/  dts; int /*<<< orphan*/  state; int /*<<< orphan*/  lock; int /*<<< orphan*/  run_work; struct delta_dev* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELTA_PREFIX ; 
 int /*<<< orphan*/  DELTA_STATE_WF_FORMAT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ clk_prepare_enable (scalar_t__) ; 
 int /*<<< orphan*/  delta_run_work ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  kfree (struct delta_ctx*) ; 
 struct delta_ctx* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_init ; 
 int /*<<< orphan*/  set_default_params (struct delta_ctx*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int) ; 
 int /*<<< orphan*/  v4l2_fh_add (TYPE_1__*) ; 
 int /*<<< orphan*/  v4l2_fh_del (TYPE_1__*) ; 
 int /*<<< orphan*/  v4l2_fh_exit (TYPE_1__*) ; 
 int /*<<< orphan*/  v4l2_fh_init (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_m2m_ctx_init (int /*<<< orphan*/ ,struct delta_ctx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  video_devdata (struct file*) ; 
 struct delta_dev* video_drvdata (struct file*) ; 

__attribute__((used)) static int delta_open(struct file *file)
{
	struct delta_dev *delta = video_drvdata(file);
	struct delta_ctx *ctx = NULL;
	int ret = 0;

	mutex_lock(&delta->lock);

	ctx = kzalloc(sizeof(*ctx), GFP_KERNEL);
	if (!ctx) {
		ret = -ENOMEM;
		goto err;
	}
	ctx->dev = delta;

	v4l2_fh_init(&ctx->fh, video_devdata(file));
	file->private_data = &ctx->fh;
	v4l2_fh_add(&ctx->fh);

	INIT_WORK(&ctx->run_work, delta_run_work);
	mutex_init(&ctx->lock);

	ctx->fh.m2m_ctx = v4l2_m2m_ctx_init(delta->m2m_dev, ctx,
					    queue_init);
	if (IS_ERR(ctx->fh.m2m_ctx)) {
		ret = PTR_ERR(ctx->fh.m2m_ctx);
		dev_err(delta->dev, "%s failed to initialize m2m context (%d)\n",
			DELTA_PREFIX, ret);
		goto err_fh_del;
	}

	/*
	 * wait stream format to determine which
	 * decoder to open
	 */
	ctx->state = DELTA_STATE_WF_FORMAT;

	INIT_LIST_HEAD(&ctx->dts);

	/* set the instance name */
	delta->instance_id++;
	snprintf(ctx->name, sizeof(ctx->name), "[%3d:----]",
		 delta->instance_id);

	/* default parameters for frame and stream */
	set_default_params(ctx);

	/* enable ST231 clocks */
	if (delta->clk_st231)
		if (clk_prepare_enable(delta->clk_st231))
			dev_warn(delta->dev, "failed to enable st231 clk\n");

	/* enable FLASH_PROMIP clock */
	if (delta->clk_flash_promip)
		if (clk_prepare_enable(delta->clk_flash_promip))
			dev_warn(delta->dev, "failed to enable delta promip clk\n");

	mutex_unlock(&delta->lock);

	dev_dbg(delta->dev, "%s decoder instance created\n", ctx->name);

	return 0;

err_fh_del:
	v4l2_fh_del(&ctx->fh);
	v4l2_fh_exit(&ctx->fh);
	kfree(ctx);
err:
	mutex_unlock(&delta->lock);

	return ret;
}
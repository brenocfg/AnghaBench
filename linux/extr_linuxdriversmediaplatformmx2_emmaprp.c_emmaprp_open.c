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
struct file {struct emmaprp_ctx* private_data; } ;
struct emmaprp_dev {int /*<<< orphan*/  dev_mutex; int /*<<< orphan*/  clk_emma_ahb; int /*<<< orphan*/  clk_emma_ipg; int /*<<< orphan*/  m2m_dev; } ;
struct emmaprp_ctx {int /*<<< orphan*/  m2m_ctx; TYPE_1__* q_data; struct emmaprp_dev* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/ * fmt; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ERESTARTSYS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 size_t V4L2_M2M_DST ; 
 size_t V4L2_M2M_SRC ; 
 int /*<<< orphan*/  clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintk (struct emmaprp_dev*,char*,struct emmaprp_ctx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * formats ; 
 int /*<<< orphan*/  kfree (struct emmaprp_ctx*) ; 
 struct emmaprp_ctx* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_init ; 
 int /*<<< orphan*/  v4l2_m2m_ctx_init (int /*<<< orphan*/ ,struct emmaprp_ctx*,int /*<<< orphan*/ *) ; 
 struct emmaprp_dev* video_drvdata (struct file*) ; 

__attribute__((used)) static int emmaprp_open(struct file *file)
{
	struct emmaprp_dev *pcdev = video_drvdata(file);
	struct emmaprp_ctx *ctx;

	ctx = kzalloc(sizeof *ctx, GFP_KERNEL);
	if (!ctx)
		return -ENOMEM;

	file->private_data = ctx;
	ctx->dev = pcdev;

	if (mutex_lock_interruptible(&pcdev->dev_mutex)) {
		kfree(ctx);
		return -ERESTARTSYS;
	}

	ctx->m2m_ctx = v4l2_m2m_ctx_init(pcdev->m2m_dev, ctx, &queue_init);

	if (IS_ERR(ctx->m2m_ctx)) {
		int ret = PTR_ERR(ctx->m2m_ctx);

		mutex_unlock(&pcdev->dev_mutex);
		kfree(ctx);
		return ret;
	}

	clk_prepare_enable(pcdev->clk_emma_ipg);
	clk_prepare_enable(pcdev->clk_emma_ahb);
	ctx->q_data[V4L2_M2M_SRC].fmt = &formats[1];
	ctx->q_data[V4L2_M2M_DST].fmt = &formats[0];
	mutex_unlock(&pcdev->dev_mutex);

	dprintk(pcdev, "Created instance %p, m2m_ctx: %p\n", ctx, ctx->m2m_ctx);

	return 0;
}
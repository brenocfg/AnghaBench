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
struct file {TYPE_1__* private_data; } ;
struct dma_interleaved_template {int dummy; } ;
struct deinterlace_dev {int /*<<< orphan*/  m2m_dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  m2m_ctx; } ;
struct deinterlace_ctx {TYPE_1__ fh; int /*<<< orphan*/  colorspace; void* xt; struct deinterlace_dev* dev; } ;
struct data_chunk {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V4L2_COLORSPACE_REC709 ; 
 int /*<<< orphan*/  dprintk (struct deinterlace_dev*,char*,struct deinterlace_ctx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct deinterlace_ctx*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_init ; 
 int /*<<< orphan*/  v4l2_fh_add (TYPE_1__*) ; 
 int /*<<< orphan*/  v4l2_fh_init (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_m2m_ctx_init (int /*<<< orphan*/ ,struct deinterlace_ctx*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  video_devdata (struct file*) ; 
 struct deinterlace_dev* video_drvdata (struct file*) ; 

__attribute__((used)) static int deinterlace_open(struct file *file)
{
	struct deinterlace_dev *pcdev = video_drvdata(file);
	struct deinterlace_ctx *ctx = NULL;

	ctx = kzalloc(sizeof *ctx, GFP_KERNEL);
	if (!ctx)
		return -ENOMEM;

	v4l2_fh_init(&ctx->fh, video_devdata(file));
	file->private_data = &ctx->fh;
	ctx->dev = pcdev;

	ctx->fh.m2m_ctx = v4l2_m2m_ctx_init(pcdev->m2m_dev, ctx, &queue_init);
	if (IS_ERR(ctx->fh.m2m_ctx)) {
		int ret = PTR_ERR(ctx->fh.m2m_ctx);

		kfree(ctx);
		return ret;
	}

	ctx->xt = kzalloc(sizeof(struct dma_interleaved_template) +
				sizeof(struct data_chunk), GFP_KERNEL);
	if (!ctx->xt) {
		kfree(ctx);
		return -ENOMEM;
	}

	ctx->colorspace = V4L2_COLORSPACE_REC709;
	v4l2_fh_add(&ctx->fh);

	dprintk(pcdev, "Created instance %p, m2m_ctx: %p\n",
		ctx, ctx->fh.m2m_ctx);

	return 0;
}
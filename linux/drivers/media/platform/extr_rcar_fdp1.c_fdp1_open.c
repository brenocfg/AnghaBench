#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct v4l2_pix_format_mplane {int dummy; } ;
struct v4l2_ctrl {int /*<<< orphan*/  flags; } ;
struct file {TYPE_1__* private_data; } ;
struct fdp1_dev {int /*<<< orphan*/  dev_mutex; int /*<<< orphan*/  dev; int /*<<< orphan*/  m2m_dev; } ;
struct TYPE_8__ {int /*<<< orphan*/  m2m_ctx; TYPE_3__* ctrl_handler; } ;
struct TYPE_9__ {int error; } ;
struct fdp1_ctx {int translen; TYPE_1__ fh; TYPE_3__ hdl; scalar_t__ sequence; int /*<<< orphan*/  fields_queue; struct fdp1_dev* fdp1; } ;
typedef  int /*<<< orphan*/  format ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int ERESTARTSYS ; 
 int /*<<< orphan*/  FDP1_FIXED3D ; 
 int /*<<< orphan*/  FDP1_NEXTFIELD ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE ; 
 int /*<<< orphan*/  V4L2_CID_ALPHA_COMPONENT ; 
 int /*<<< orphan*/  V4L2_CID_DEINTERLACING_MODE ; 
 int /*<<< orphan*/  V4L2_CID_MIN_BUFFERS_FOR_CAPTURE ; 
 int /*<<< orphan*/  V4L2_CTRL_FLAG_VOLATILE ; 
 int /*<<< orphan*/  dprintk (struct fdp1_dev*,char*,struct fdp1_ctx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fdp1_ctrl_deint_menu ; 
 int /*<<< orphan*/  fdp1_ctrl_ops ; 
 int /*<<< orphan*/  fdp1_set_format (struct fdp1_ctx*,struct v4l2_pix_format_mplane*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct fdp1_ctx*) ; 
 struct fdp1_ctx* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct v4l2_pix_format_mplane*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_init ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (TYPE_3__*) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_init (TYPE_3__*,int) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_setup (TYPE_3__*) ; 
 struct v4l2_ctrl* v4l2_ctrl_new_std (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/  v4l2_ctrl_new_std_menu_items (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_fh_add (TYPE_1__*) ; 
 int /*<<< orphan*/  v4l2_fh_init (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_m2m_ctx_init (int /*<<< orphan*/ ,struct fdp1_ctx*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  video_devdata (struct file*) ; 
 struct fdp1_dev* video_drvdata (struct file*) ; 

__attribute__((used)) static int fdp1_open(struct file *file)
{
	struct fdp1_dev *fdp1 = video_drvdata(file);
	struct v4l2_pix_format_mplane format;
	struct fdp1_ctx *ctx = NULL;
	struct v4l2_ctrl *ctrl;
	int ret = 0;

	if (mutex_lock_interruptible(&fdp1->dev_mutex))
		return -ERESTARTSYS;

	ctx = kzalloc(sizeof(*ctx), GFP_KERNEL);
	if (!ctx) {
		ret = -ENOMEM;
		goto done;
	}

	v4l2_fh_init(&ctx->fh, video_devdata(file));
	file->private_data = &ctx->fh;
	ctx->fdp1 = fdp1;

	/* Initialise Queues */
	INIT_LIST_HEAD(&ctx->fields_queue);

	ctx->translen = 1;
	ctx->sequence = 0;

	/* Initialise controls */

	v4l2_ctrl_handler_init(&ctx->hdl, 3);
	v4l2_ctrl_new_std_menu_items(&ctx->hdl, &fdp1_ctrl_ops,
				     V4L2_CID_DEINTERLACING_MODE,
				     FDP1_NEXTFIELD, BIT(0), FDP1_FIXED3D,
				     fdp1_ctrl_deint_menu);

	ctrl = v4l2_ctrl_new_std(&ctx->hdl, &fdp1_ctrl_ops,
				 V4L2_CID_MIN_BUFFERS_FOR_CAPTURE, 1, 2, 1, 1);
	if (ctrl)
		ctrl->flags |= V4L2_CTRL_FLAG_VOLATILE;

	v4l2_ctrl_new_std(&ctx->hdl, &fdp1_ctrl_ops,
			  V4L2_CID_ALPHA_COMPONENT, 0, 255, 1, 255);

	if (ctx->hdl.error) {
		ret = ctx->hdl.error;
		v4l2_ctrl_handler_free(&ctx->hdl);
		kfree(ctx);
		goto done;
	}

	ctx->fh.ctrl_handler = &ctx->hdl;
	v4l2_ctrl_handler_setup(&ctx->hdl);

	/* Configure default parameters. */
	memset(&format, 0, sizeof(format));
	fdp1_set_format(ctx, &format, V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE);

	ctx->fh.m2m_ctx = v4l2_m2m_ctx_init(fdp1->m2m_dev, ctx, &queue_init);

	if (IS_ERR(ctx->fh.m2m_ctx)) {
		ret = PTR_ERR(ctx->fh.m2m_ctx);

		v4l2_ctrl_handler_free(&ctx->hdl);
		kfree(ctx);
		goto done;
	}

	/* Perform any power management required */
	pm_runtime_get_sync(fdp1->dev);

	v4l2_fh_add(&ctx->fh);

	dprintk(fdp1, "Created instance: %p, m2m_ctx: %p\n",
		ctx, ctx->fh.m2m_ctx);

done:
	mutex_unlock(&fdp1->dev_mutex);
	return ret;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  refcnt; int /*<<< orphan*/  m2m_dev; int /*<<< orphan*/  vfd; } ;
struct gsc_dev {int /*<<< orphan*/  lock; int /*<<< orphan*/  state; TYPE_3__ m2m; } ;
struct TYPE_11__ {int /*<<< orphan*/ * ctrl_handler; } ;
struct TYPE_9__ {void* fmt; } ;
struct TYPE_8__ {void* fmt; } ;
struct gsc_ctx {TYPE_4__ fh; int /*<<< orphan*/  m2m_ctx; void* out_path; void* in_path; scalar_t__ flags; int /*<<< orphan*/  state; TYPE_2__ d_frame; TYPE_1__ s_frame; struct gsc_dev* gsc_dev; int /*<<< orphan*/  ctrl_handler; } ;
struct file {TYPE_4__* private_data; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ERESTARTSYS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GSC_CTX_M2M ; 
 void* GSC_DMA ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ST_M2M_OPEN ; 
 int /*<<< orphan*/  current ; 
 void* get_format (int /*<<< orphan*/ ) ; 
 int gsc_ctrls_create (struct gsc_ctx*) ; 
 int /*<<< orphan*/  gsc_ctrls_delete (struct gsc_ctx*) ; 
 int /*<<< orphan*/  kfree (struct gsc_ctx*) ; 
 struct gsc_ctx* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,struct gsc_ctx*,...) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  queue_init ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  task_pid_nr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_fh_add (TYPE_4__*) ; 
 int /*<<< orphan*/  v4l2_fh_del (TYPE_4__*) ; 
 int /*<<< orphan*/  v4l2_fh_exit (TYPE_4__*) ; 
 int /*<<< orphan*/  v4l2_fh_init (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_m2m_ctx_init (int /*<<< orphan*/ ,struct gsc_ctx*,int /*<<< orphan*/ ) ; 
 struct gsc_dev* video_drvdata (struct file*) ; 

__attribute__((used)) static int gsc_m2m_open(struct file *file)
{
	struct gsc_dev *gsc = video_drvdata(file);
	struct gsc_ctx *ctx = NULL;
	int ret;

	pr_debug("pid: %d, state: 0x%lx", task_pid_nr(current), gsc->state);

	if (mutex_lock_interruptible(&gsc->lock))
		return -ERESTARTSYS;

	ctx = kzalloc(sizeof(*ctx), GFP_KERNEL);
	if (!ctx) {
		ret = -ENOMEM;
		goto unlock;
	}

	v4l2_fh_init(&ctx->fh, gsc->m2m.vfd);
	ret = gsc_ctrls_create(ctx);
	if (ret)
		goto error_fh;

	/* Use separate control handler per file handle */
	ctx->fh.ctrl_handler = &ctx->ctrl_handler;
	file->private_data = &ctx->fh;
	v4l2_fh_add(&ctx->fh);

	ctx->gsc_dev = gsc;
	/* Default color format */
	ctx->s_frame.fmt = get_format(0);
	ctx->d_frame.fmt = get_format(0);
	/* Setup the device context for mem2mem mode. */
	ctx->state = GSC_CTX_M2M;
	ctx->flags = 0;
	ctx->in_path = GSC_DMA;
	ctx->out_path = GSC_DMA;

	ctx->m2m_ctx = v4l2_m2m_ctx_init(gsc->m2m.m2m_dev, ctx, queue_init);
	if (IS_ERR(ctx->m2m_ctx)) {
		pr_err("Failed to initialize m2m context");
		ret = PTR_ERR(ctx->m2m_ctx);
		goto error_ctrls;
	}

	if (gsc->m2m.refcnt++ == 0)
		set_bit(ST_M2M_OPEN, &gsc->state);

	pr_debug("gsc m2m driver is opened, ctx(0x%p)", ctx);

	mutex_unlock(&gsc->lock);
	return 0;

error_ctrls:
	gsc_ctrls_delete(ctx);
	v4l2_fh_del(&ctx->fh);
error_fh:
	v4l2_fh_exit(&ctx->fh);
	kfree(ctx);
unlock:
	mutex_unlock(&gsc->lock);
	return ret;
}
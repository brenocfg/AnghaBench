#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  refcnt; int /*<<< orphan*/  m2m_dev; int /*<<< orphan*/  vfd; } ;
struct fimc_dev {int /*<<< orphan*/  lock; int /*<<< orphan*/  state; TYPE_5__ m2m; } ;
struct TYPE_15__ {int /*<<< orphan*/  m2m_ctx; int /*<<< orphan*/ * ctrl_handler; } ;
struct TYPE_13__ {int enabled; } ;
struct TYPE_12__ {int /*<<< orphan*/  handler; } ;
struct TYPE_11__ {void* fmt; } ;
struct TYPE_10__ {void* fmt; } ;
struct fimc_ctx {TYPE_6__ fh; TYPE_4__ scaler; void* out_path; void* in_path; scalar_t__ flags; int /*<<< orphan*/  state; TYPE_3__ ctrls; TYPE_2__ d_frame; TYPE_1__ s_frame; struct fimc_dev* fimc_dev; } ;
struct file {TYPE_6__* private_data; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENOMEM ; 
 int ERESTARTSYS ; 
 int /*<<< orphan*/  FIMC_CTX_M2M ; 
 void* FIMC_IO_DMA ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ST_CAPT_BUSY ; 
 int /*<<< orphan*/  ST_M2M_RUN ; 
 int /*<<< orphan*/  current ; 
 int fimc_ctrls_create (struct fimc_ctx*) ; 
 int /*<<< orphan*/  fimc_ctrls_delete (struct fimc_ctx*) ; 
 void* fimc_get_format (int /*<<< orphan*/ ) ; 
 int fimc_m2m_set_default_format (struct fimc_ctx*) ; 
 int /*<<< orphan*/  kfree (struct fimc_ctx*) ; 
 struct fimc_ctx* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_init ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  task_pid_nr (int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_fh_add (TYPE_6__*) ; 
 int /*<<< orphan*/  v4l2_fh_del (TYPE_6__*) ; 
 int /*<<< orphan*/  v4l2_fh_exit (TYPE_6__*) ; 
 int /*<<< orphan*/  v4l2_fh_init (TYPE_6__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_m2m_ctx_init (int /*<<< orphan*/ ,struct fimc_ctx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_m2m_ctx_release (int /*<<< orphan*/ ) ; 
 struct fimc_dev* video_drvdata (struct file*) ; 

__attribute__((used)) static int fimc_m2m_open(struct file *file)
{
	struct fimc_dev *fimc = video_drvdata(file);
	struct fimc_ctx *ctx;
	int ret = -EBUSY;

	pr_debug("pid: %d, state: %#lx\n", task_pid_nr(current), fimc->state);

	if (mutex_lock_interruptible(&fimc->lock))
		return -ERESTARTSYS;
	/*
	 * Don't allow simultaneous open() of the mem-to-mem and the
	 * capture video node that belong to same FIMC IP instance.
	 */
	if (test_bit(ST_CAPT_BUSY, &fimc->state))
		goto unlock;

	ctx = kzalloc(sizeof(*ctx), GFP_KERNEL);
	if (!ctx) {
		ret = -ENOMEM;
		goto unlock;
	}
	v4l2_fh_init(&ctx->fh, &fimc->m2m.vfd);
	ctx->fimc_dev = fimc;

	/* Default color format */
	ctx->s_frame.fmt = fimc_get_format(0);
	ctx->d_frame.fmt = fimc_get_format(0);

	ret = fimc_ctrls_create(ctx);
	if (ret)
		goto error_fh;

	/* Use separate control handler per file handle */
	ctx->fh.ctrl_handler = &ctx->ctrls.handler;
	file->private_data = &ctx->fh;
	v4l2_fh_add(&ctx->fh);

	/* Setup the device context for memory-to-memory mode */
	ctx->state = FIMC_CTX_M2M;
	ctx->flags = 0;
	ctx->in_path = FIMC_IO_DMA;
	ctx->out_path = FIMC_IO_DMA;
	ctx->scaler.enabled = 1;

	ctx->fh.m2m_ctx = v4l2_m2m_ctx_init(fimc->m2m.m2m_dev, ctx, queue_init);
	if (IS_ERR(ctx->fh.m2m_ctx)) {
		ret = PTR_ERR(ctx->fh.m2m_ctx);
		goto error_c;
	}

	if (fimc->m2m.refcnt++ == 0)
		set_bit(ST_M2M_RUN, &fimc->state);

	ret = fimc_m2m_set_default_format(ctx);
	if (ret < 0)
		goto error_m2m_ctx;

	mutex_unlock(&fimc->lock);
	return 0;

error_m2m_ctx:
	v4l2_m2m_ctx_release(ctx->fh.m2m_ctx);
error_c:
	fimc_ctrls_delete(ctx);
	v4l2_fh_del(&ctx->fh);
error_fh:
	v4l2_fh_exit(&ctx->fh);
	kfree(ctx);
unlock:
	mutex_unlock(&fimc->lock);
	return ret;
}
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
struct pxp_dev {int /*<<< orphan*/  num_inst; int /*<<< orphan*/  dev_mutex; } ;
struct TYPE_3__ {int /*<<< orphan*/  m2m_ctx; } ;
struct pxp_ctx {TYPE_1__ fh; int /*<<< orphan*/  hdl; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dprintk (struct pxp_dev*,char*,struct pxp_ctx*) ; 
 struct pxp_ctx* file2ctx (struct file*) ; 
 int /*<<< orphan*/  kfree (struct pxp_ctx*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_fh_del (TYPE_1__*) ; 
 int /*<<< orphan*/  v4l2_fh_exit (TYPE_1__*) ; 
 int /*<<< orphan*/  v4l2_m2m_ctx_release (int /*<<< orphan*/ ) ; 
 struct pxp_dev* video_drvdata (struct file*) ; 

__attribute__((used)) static int pxp_release(struct file *file)
{
	struct pxp_dev *dev = video_drvdata(file);
	struct pxp_ctx *ctx = file2ctx(file);

	dprintk(dev, "Releasing instance %p\n", ctx);

	v4l2_fh_del(&ctx->fh);
	v4l2_fh_exit(&ctx->fh);
	v4l2_ctrl_handler_free(&ctx->hdl);
	mutex_lock(&dev->dev_mutex);
	v4l2_m2m_ctx_release(ctx->fh.m2m_ctx);
	mutex_unlock(&dev->dev_mutex);
	kfree(ctx);

	atomic_dec(&dev->num_inst);

	return 0;
}
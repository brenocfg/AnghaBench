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
struct fdp1_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  dev_mutex; } ;
struct TYPE_3__ {int /*<<< orphan*/  m2m_ctx; } ;
struct fdp1_ctx {TYPE_1__ fh; int /*<<< orphan*/  hdl; } ;

/* Variables and functions */
 int /*<<< orphan*/  dprintk (struct fdp1_dev*,char*,struct fdp1_ctx*) ; 
 struct fdp1_ctx* fh_to_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct fdp1_ctx*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_fh_del (TYPE_1__*) ; 
 int /*<<< orphan*/  v4l2_fh_exit (TYPE_1__*) ; 
 int /*<<< orphan*/  v4l2_m2m_ctx_release (int /*<<< orphan*/ ) ; 
 struct fdp1_dev* video_drvdata (struct file*) ; 

__attribute__((used)) static int fdp1_release(struct file *file)
{
	struct fdp1_dev *fdp1 = video_drvdata(file);
	struct fdp1_ctx *ctx = fh_to_ctx(file->private_data);

	dprintk(fdp1, "Releasing instance %p\n", ctx);

	v4l2_fh_del(&ctx->fh);
	v4l2_fh_exit(&ctx->fh);
	v4l2_ctrl_handler_free(&ctx->hdl);
	mutex_lock(&fdp1->dev_mutex);
	v4l2_m2m_ctx_release(ctx->fh.m2m_ctx);
	mutex_unlock(&fdp1->dev_mutex);
	kfree(ctx);

	pm_runtime_put(fdp1->dev);

	return 0;
}
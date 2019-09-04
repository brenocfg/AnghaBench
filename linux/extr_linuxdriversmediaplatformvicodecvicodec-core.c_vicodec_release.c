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
struct video_device {int /*<<< orphan*/  lock; } ;
struct TYPE_3__ {int /*<<< orphan*/  m2m_ctx; } ;
struct vicodec_ctx {TYPE_1__ fh; int /*<<< orphan*/  hdl; } ;
struct file {int dummy; } ;

/* Variables and functions */
 struct vicodec_ctx* file2ctx (struct file*) ; 
 int /*<<< orphan*/  kfree (struct vicodec_ctx*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_fh_del (TYPE_1__*) ; 
 int /*<<< orphan*/  v4l2_fh_exit (TYPE_1__*) ; 
 int /*<<< orphan*/  v4l2_m2m_ctx_release (int /*<<< orphan*/ ) ; 
 struct video_device* video_devdata (struct file*) ; 

__attribute__((used)) static int vicodec_release(struct file *file)
{
	struct video_device *vfd = video_devdata(file);
	struct vicodec_ctx *ctx = file2ctx(file);

	v4l2_fh_del(&ctx->fh);
	v4l2_fh_exit(&ctx->fh);
	v4l2_ctrl_handler_free(&ctx->hdl);
	mutex_lock(vfd->lock);
	v4l2_m2m_ctx_release(ctx->fh.m2m_ctx);
	mutex_unlock(vfd->lock);
	kfree(ctx);

	return 0;
}
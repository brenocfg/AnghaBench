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
struct TYPE_3__ {int /*<<< orphan*/  m2m_ctx; } ;
struct jpu_ctx {TYPE_1__ fh; int /*<<< orphan*/  ctrl_handler; } ;
struct jpu {scalar_t__ ref_count; int /*<<< orphan*/  mutex; int /*<<< orphan*/  clk; } ;
struct file {int /*<<< orphan*/  private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct jpu_ctx* fh_to_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct jpu_ctx*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_fh_del (TYPE_1__*) ; 
 int /*<<< orphan*/  v4l2_fh_exit (TYPE_1__*) ; 
 int /*<<< orphan*/  v4l2_m2m_ctx_release (int /*<<< orphan*/ ) ; 
 struct jpu* video_drvdata (struct file*) ; 

__attribute__((used)) static int jpu_release(struct file *file)
{
	struct jpu *jpu = video_drvdata(file);
	struct jpu_ctx *ctx = fh_to_ctx(file->private_data);

	v4l2_m2m_ctx_release(ctx->fh.m2m_ctx);
	v4l2_ctrl_handler_free(&ctx->ctrl_handler);
	v4l2_fh_del(&ctx->fh);
	v4l2_fh_exit(&ctx->fh);
	kfree(ctx);

	mutex_lock(&jpu->mutex);
	if (--jpu->ref_count == 0)
		clk_disable_unprepare(jpu->clk);
	mutex_unlock(&jpu->mutex);

	return 0;
}
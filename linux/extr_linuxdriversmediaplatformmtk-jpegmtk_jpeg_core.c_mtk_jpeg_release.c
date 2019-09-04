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
struct mtk_jpeg_dev {int /*<<< orphan*/  lock; } ;
struct TYPE_3__ {int /*<<< orphan*/  m2m_ctx; } ;
struct mtk_jpeg_ctx {TYPE_1__ fh; } ;
struct file {int /*<<< orphan*/  private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct mtk_jpeg_ctx*) ; 
 struct mtk_jpeg_ctx* mtk_jpeg_fh_to_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_fh_del (TYPE_1__*) ; 
 int /*<<< orphan*/  v4l2_fh_exit (TYPE_1__*) ; 
 int /*<<< orphan*/  v4l2_m2m_ctx_release (int /*<<< orphan*/ ) ; 
 struct mtk_jpeg_dev* video_drvdata (struct file*) ; 

__attribute__((used)) static int mtk_jpeg_release(struct file *file)
{
	struct mtk_jpeg_dev *jpeg = video_drvdata(file);
	struct mtk_jpeg_ctx *ctx = mtk_jpeg_fh_to_ctx(file->private_data);

	mutex_lock(&jpeg->lock);
	v4l2_m2m_ctx_release(ctx->fh.m2m_ctx);
	v4l2_fh_del(&ctx->fh);
	v4l2_fh_exit(&ctx->fh);
	kfree(ctx);
	mutex_unlock(&jpeg->lock);
	return 0;
}
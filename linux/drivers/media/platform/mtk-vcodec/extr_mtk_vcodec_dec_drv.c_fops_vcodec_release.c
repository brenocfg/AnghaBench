#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct mtk_vcodec_dev {int /*<<< orphan*/  dev_mutex; int /*<<< orphan*/  pm; } ;
struct mtk_vcodec_ctx {struct mtk_vcodec_ctx* empty_flush_buf; int /*<<< orphan*/  list; int /*<<< orphan*/  ctrl_hdl; int /*<<< orphan*/  fh; int /*<<< orphan*/  m2m_ctx; int /*<<< orphan*/  id; } ;
struct file {int /*<<< orphan*/  private_data; } ;

/* Variables and functions */
 struct mtk_vcodec_ctx* fh_to_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct mtk_vcodec_ctx*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtk_v4l2_debug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_vcodec_dec_pw_off (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtk_vcodec_dec_release (struct mtk_vcodec_ctx*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_fh_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_fh_exit (int /*<<< orphan*/ *) ; 
 scalar_t__ v4l2_fh_is_singular (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_m2m_ctx_release (int /*<<< orphan*/ ) ; 
 struct mtk_vcodec_dev* video_drvdata (struct file*) ; 

__attribute__((used)) static int fops_vcodec_release(struct file *file)
{
	struct mtk_vcodec_dev *dev = video_drvdata(file);
	struct mtk_vcodec_ctx *ctx = fh_to_ctx(file->private_data);

	mtk_v4l2_debug(0, "[%d] decoder", ctx->id);
	mutex_lock(&dev->dev_mutex);

	/*
	 * Call v4l2_m2m_ctx_release before mtk_vcodec_dec_release. First, it
	 * makes sure the worker thread is not running after vdec_if_deinit.
	 * Second, the decoder will be flushed and all the buffers will be
	 * returned in stop_streaming.
	 */
	v4l2_m2m_ctx_release(ctx->m2m_ctx);
	mtk_vcodec_dec_release(ctx);

	if (v4l2_fh_is_singular(&ctx->fh))
		mtk_vcodec_dec_pw_off(&dev->pm);
	v4l2_fh_del(&ctx->fh);
	v4l2_fh_exit(&ctx->fh);
	v4l2_ctrl_handler_free(&ctx->ctrl_hdl);

	list_del_init(&ctx->list);
	kfree(ctx->empty_flush_buf);
	kfree(ctx);
	mutex_unlock(&dev->dev_mutex);
	return 0;
}
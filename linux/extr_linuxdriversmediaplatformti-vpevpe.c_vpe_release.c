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
struct vpe_dev {int /*<<< orphan*/  dev_mutex; int /*<<< orphan*/  num_instances; } ;
struct TYPE_3__ {int /*<<< orphan*/  m2m_ctx; } ;
struct vpe_ctx {TYPE_1__ fh; int /*<<< orphan*/  hdl; int /*<<< orphan*/  sc_coeff_h; int /*<<< orphan*/  sc_coeff_v; int /*<<< orphan*/  mmr_adb; int /*<<< orphan*/  desc_list; } ;
struct file {int dummy; } ;

/* Variables and functions */
 scalar_t__ atomic_dec_return (int /*<<< orphan*/ *) ; 
 struct vpe_ctx* file2ctx (struct file*) ; 
 int /*<<< orphan*/  free_mv_buffers (struct vpe_ctx*) ; 
 int /*<<< orphan*/  kfree (struct vpe_ctx*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_fh_del (TYPE_1__*) ; 
 int /*<<< orphan*/  v4l2_fh_exit (TYPE_1__*) ; 
 int /*<<< orphan*/  v4l2_m2m_ctx_release (int /*<<< orphan*/ ) ; 
 struct vpe_dev* video_drvdata (struct file*) ; 
 int /*<<< orphan*/  vpdma_free_desc_buf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vpdma_free_desc_list (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vpe_dbg (struct vpe_dev*,char*,...) ; 

__attribute__((used)) static int vpe_release(struct file *file)
{
	struct vpe_dev *dev = video_drvdata(file);
	struct vpe_ctx *ctx = file2ctx(file);

	vpe_dbg(dev, "releasing instance %p\n", ctx);

	mutex_lock(&dev->dev_mutex);
	free_mv_buffers(ctx);
	vpdma_free_desc_list(&ctx->desc_list);
	vpdma_free_desc_buf(&ctx->mmr_adb);

	vpdma_free_desc_buf(&ctx->sc_coeff_v);
	vpdma_free_desc_buf(&ctx->sc_coeff_h);

	v4l2_fh_del(&ctx->fh);
	v4l2_fh_exit(&ctx->fh);
	v4l2_ctrl_handler_free(&ctx->hdl);
	v4l2_m2m_ctx_release(ctx->fh.m2m_ctx);

	kfree(ctx);

	/*
	 * for now, just report the release of the last instance, we can later
	 * optimize the driver to enable or disable clocks when the first
	 * instance is created or the last instance released
	 */
	if (atomic_dec_return(&dev->num_instances) == 0)
		vpe_dbg(dev, "last instance released\n");

	mutex_unlock(&dev->dev_mutex);

	return 0;
}
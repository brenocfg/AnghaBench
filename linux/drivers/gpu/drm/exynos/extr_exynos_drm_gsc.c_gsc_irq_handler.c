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
typedef  int u32 ;
struct gsc_context {int /*<<< orphan*/  dev; struct exynos_drm_ipp_task* task; int /*<<< orphan*/  id; } ;
struct exynos_drm_ipp_task {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_DEBUG_KMS (int /*<<< orphan*/ ,char*,int,...) ; 
 int EINVAL ; 
 int /*<<< orphan*/  GSC_IRQ ; 
 int GSC_IRQ_STATUS_OR_FRM_DONE ; 
 int GSC_IRQ_STATUS_OR_IRQ ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  exynos_drm_ipp_task_done (struct exynos_drm_ipp_task*,int) ; 
 int gsc_get_dst_buf_index (struct gsc_context*) ; 
 int gsc_get_src_buf_index (struct gsc_context*) ; 
 int gsc_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t gsc_irq_handler(int irq, void *dev_id)
{
	struct gsc_context *ctx = dev_id;
	u32 status;
	int err = 0;

	DRM_DEV_DEBUG_KMS(ctx->dev, "gsc id[%d]\n", ctx->id);

	status = gsc_read(GSC_IRQ);
	if (status & GSC_IRQ_STATUS_OR_IRQ) {
		dev_err(ctx->dev, "occurred overflow at %d, status 0x%x.\n",
			ctx->id, status);
		err = -EINVAL;
	}

	if (status & GSC_IRQ_STATUS_OR_FRM_DONE) {
		int src_buf_id, dst_buf_id;

		dev_dbg(ctx->dev, "occurred frame done at %d, status 0x%x.\n",
			ctx->id, status);

		src_buf_id = gsc_get_src_buf_index(ctx);
		dst_buf_id = gsc_get_dst_buf_index(ctx);

		DRM_DEV_DEBUG_KMS(ctx->dev, "buf_id_src[%d]buf_id_dst[%d]\n",
				  src_buf_id, dst_buf_id);

		if (src_buf_id < 0 || dst_buf_id < 0)
			err = -EINVAL;
	}

	if (ctx->task) {
		struct exynos_drm_ipp_task *task = ctx->task;

		ctx->task = NULL;
		pm_runtime_mark_last_busy(ctx->dev);
		pm_runtime_put_autosuspend(ctx->dev);
		exynos_drm_ipp_task_done(task, err);
	}

	return IRQ_HANDLED;
}
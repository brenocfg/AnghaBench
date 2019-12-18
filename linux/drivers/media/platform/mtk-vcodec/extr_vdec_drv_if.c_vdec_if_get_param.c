#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mtk_vcodec_ctx {int /*<<< orphan*/  drv_handle; TYPE_1__* dec_if; } ;
typedef  enum vdec_get_param_type { ____Placeholder_vdec_get_param_type } vdec_get_param_type ;
struct TYPE_2__ {int (* get_param ) (int /*<<< orphan*/ ,int,void*) ;} ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  mtk_vdec_lock (struct mtk_vcodec_ctx*) ; 
 int /*<<< orphan*/  mtk_vdec_unlock (struct mtk_vcodec_ctx*) ; 
 int stub1 (int /*<<< orphan*/ ,int,void*) ; 

int vdec_if_get_param(struct mtk_vcodec_ctx *ctx, enum vdec_get_param_type type,
		      void *out)
{
	int ret = 0;

	if (!ctx->drv_handle)
		return -EIO;

	mtk_vdec_lock(ctx);
	ret = ctx->dec_if->get_param(ctx->drv_handle, type, out);
	mtk_vdec_unlock(ctx);

	return ret;
}
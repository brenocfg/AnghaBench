#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ pic_w; scalar_t__ pic_h; } ;
struct TYPE_3__ {scalar_t__ pic_w; scalar_t__ pic_h; } ;
struct mtk_vcodec_ctx {scalar_t__ state; TYPE_2__ picinfo; TYPE_1__ last_decoded_picinfo; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 scalar_t__ MTK_STATE_ABORT ; 
 scalar_t__ MTK_STATE_HEADER ; 
 int /*<<< orphan*/  mtk_v4l2_debug (int,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int m2mops_vdec_job_ready(void *m2m_priv)
{
	struct mtk_vcodec_ctx *ctx = m2m_priv;

	mtk_v4l2_debug(3, "[%d]", ctx->id);

	if (ctx->state == MTK_STATE_ABORT)
		return 0;

	if ((ctx->last_decoded_picinfo.pic_w != ctx->picinfo.pic_w) ||
	    (ctx->last_decoded_picinfo.pic_h != ctx->picinfo.pic_h))
		return 0;

	if (ctx->state != MTK_STATE_HEADER)
		return 0;

	return 1;
}
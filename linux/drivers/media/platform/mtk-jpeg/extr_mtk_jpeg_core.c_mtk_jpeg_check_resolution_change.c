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
struct mtk_jpeg_q_data {scalar_t__ w; scalar_t__ h; scalar_t__ fmt; } ;
struct mtk_jpeg_dev {int /*<<< orphan*/  v4l2_dev; } ;
struct mtk_jpeg_dec_param {scalar_t__ pic_w; scalar_t__ pic_h; int /*<<< orphan*/  dst_fourcc; } ;
struct mtk_jpeg_ctx {struct mtk_jpeg_q_data cap_q; struct mtk_jpeg_q_data out_q; struct mtk_jpeg_dev* jpeg; } ;

/* Variables and functions */
 int /*<<< orphan*/  MTK_JPEG_FMT_TYPE_CAPTURE ; 
 int /*<<< orphan*/  debug ; 
 scalar_t__ mtk_jpeg_find_format (struct mtk_jpeg_ctx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static bool mtk_jpeg_check_resolution_change(struct mtk_jpeg_ctx *ctx,
					     struct mtk_jpeg_dec_param *param)
{
	struct mtk_jpeg_dev *jpeg = ctx->jpeg;
	struct mtk_jpeg_q_data *q_data;

	q_data = &ctx->out_q;
	if (q_data->w != param->pic_w || q_data->h != param->pic_h) {
		v4l2_dbg(1, debug, &jpeg->v4l2_dev, "Picture size change\n");
		return true;
	}

	q_data = &ctx->cap_q;
	if (q_data->fmt != mtk_jpeg_find_format(ctx, param->dst_fourcc,
						MTK_JPEG_FMT_TYPE_CAPTURE)) {
		v4l2_dbg(1, debug, &jpeg->v4l2_dev, "format change\n");
		return true;
	}
	return false;
}
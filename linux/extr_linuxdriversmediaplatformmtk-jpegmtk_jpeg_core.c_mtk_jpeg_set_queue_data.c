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
struct mtk_jpeg_q_data {int /*<<< orphan*/ * sizeimage; int /*<<< orphan*/ * bytesperline; TYPE_1__* fmt; int /*<<< orphan*/  h; int /*<<< orphan*/  w; } ;
struct mtk_jpeg_dev {int /*<<< orphan*/  v4l2_dev; } ;
struct mtk_jpeg_dec_param {int dst_fourcc; int /*<<< orphan*/  dec_h; int /*<<< orphan*/  dec_w; int /*<<< orphan*/  pic_h; int /*<<< orphan*/  pic_w; int /*<<< orphan*/ * comp_size; int /*<<< orphan*/ * mem_stride; } ;
struct mtk_jpeg_ctx {struct mtk_jpeg_q_data cap_q; struct mtk_jpeg_q_data out_q; struct mtk_jpeg_dev* jpeg; } ;
struct TYPE_2__ {int colplanes; } ;

/* Variables and functions */
 int /*<<< orphan*/  MTK_JPEG_FMT_TYPE_CAPTURE ; 
 int /*<<< orphan*/  debug ; 
 TYPE_1__* mtk_jpeg_find_format (struct mtk_jpeg_ctx*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mtk_jpeg_set_queue_data(struct mtk_jpeg_ctx *ctx,
				    struct mtk_jpeg_dec_param *param)
{
	struct mtk_jpeg_dev *jpeg = ctx->jpeg;
	struct mtk_jpeg_q_data *q_data;
	int i;

	q_data = &ctx->out_q;
	q_data->w = param->pic_w;
	q_data->h = param->pic_h;

	q_data = &ctx->cap_q;
	q_data->w = param->dec_w;
	q_data->h = param->dec_h;
	q_data->fmt = mtk_jpeg_find_format(ctx,
					   param->dst_fourcc,
					   MTK_JPEG_FMT_TYPE_CAPTURE);

	for (i = 0; i < q_data->fmt->colplanes; i++) {
		q_data->bytesperline[i] = param->mem_stride[i];
		q_data->sizeimage[i] = param->comp_size[i];
	}

	v4l2_dbg(1, debug, &jpeg->v4l2_dev,
		 "set_parse cap:%c%c%c%c pic(%u, %u), buf(%u, %u)\n",
		 (param->dst_fourcc & 0xff),
		 (param->dst_fourcc >>  8 & 0xff),
		 (param->dst_fourcc >> 16 & 0xff),
		 (param->dst_fourcc >> 24 & 0xff),
		 param->pic_w, param->pic_h,
		 param->dec_w, param->dec_h);
}
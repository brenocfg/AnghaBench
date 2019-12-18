#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int framerate; int /*<<< orphan*/  codec_mode; } ;
struct coda_ctx {int /*<<< orphan*/  tiled_map_type; TYPE_4__* q_data; TYPE_5__* codec; TYPE_2__* cvd; TYPE_1__ params; int /*<<< orphan*/  quantization; int /*<<< orphan*/  ycbcr_enc; int /*<<< orphan*/  xfer_func; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  dev; } ;
struct TYPE_10__ {scalar_t__ src_fourcc; int /*<<< orphan*/  mode; int /*<<< orphan*/  max_h; int /*<<< orphan*/  max_w; } ;
struct TYPE_8__ {unsigned int width; unsigned int height; } ;
struct TYPE_9__ {scalar_t__ fourcc; unsigned int width; unsigned int height; unsigned int bytesperline; unsigned int sizeimage; TYPE_3__ rect; } ;
struct TYPE_7__ {scalar_t__* src_formats; scalar_t__* dst_formats; } ;

/* Variables and functions */
 int /*<<< orphan*/  GDI_LINEAR_FRAME_MAP ; 
 int /*<<< orphan*/  V4L2_COLORSPACE_JPEG ; 
 int /*<<< orphan*/  V4L2_COLORSPACE_REC709 ; 
 size_t V4L2_M2M_DST ; 
 size_t V4L2_M2M_SRC ; 
 scalar_t__ V4L2_PIX_FMT_JPEG ; 
 scalar_t__ V4L2_PIX_FMT_YUV420 ; 
 int /*<<< orphan*/  V4L2_QUANTIZATION_DEFAULT ; 
 int /*<<< orphan*/  V4L2_XFER_FUNC_DEFAULT ; 
 int /*<<< orphan*/  V4L2_YCBCR_ENC_DEFAULT ; 
 unsigned int coda_estimate_sizeimage (struct coda_ctx*,unsigned int,unsigned int,unsigned int) ; 
 TYPE_5__* coda_find_codec (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 unsigned int min (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void set_default_params(struct coda_ctx *ctx)
{
	unsigned int max_w, max_h, usize, csize;

	ctx->codec = coda_find_codec(ctx->dev, ctx->cvd->src_formats[0],
				     ctx->cvd->dst_formats[0]);
	max_w = min(ctx->codec->max_w, 1920U);
	max_h = min(ctx->codec->max_h, 1088U);
	usize = max_w * max_h * 3 / 2;
	csize = coda_estimate_sizeimage(ctx, usize, max_w, max_h);

	ctx->params.codec_mode = ctx->codec->mode;
	if (ctx->cvd->src_formats[0] == V4L2_PIX_FMT_JPEG)
		ctx->colorspace = V4L2_COLORSPACE_JPEG;
	else
		ctx->colorspace = V4L2_COLORSPACE_REC709;
	ctx->xfer_func = V4L2_XFER_FUNC_DEFAULT;
	ctx->ycbcr_enc = V4L2_YCBCR_ENC_DEFAULT;
	ctx->quantization = V4L2_QUANTIZATION_DEFAULT;
	ctx->params.framerate = 30;

	/* Default formats for output and input queues */
	ctx->q_data[V4L2_M2M_SRC].fourcc = ctx->cvd->src_formats[0];
	ctx->q_data[V4L2_M2M_DST].fourcc = ctx->cvd->dst_formats[0];
	ctx->q_data[V4L2_M2M_SRC].width = max_w;
	ctx->q_data[V4L2_M2M_SRC].height = max_h;
	ctx->q_data[V4L2_M2M_DST].width = max_w;
	ctx->q_data[V4L2_M2M_DST].height = max_h;
	if (ctx->codec->src_fourcc == V4L2_PIX_FMT_YUV420) {
		ctx->q_data[V4L2_M2M_SRC].bytesperline = max_w;
		ctx->q_data[V4L2_M2M_SRC].sizeimage = usize;
		ctx->q_data[V4L2_M2M_DST].bytesperline = 0;
		ctx->q_data[V4L2_M2M_DST].sizeimage = csize;
	} else {
		ctx->q_data[V4L2_M2M_SRC].bytesperline = 0;
		ctx->q_data[V4L2_M2M_SRC].sizeimage = csize;
		ctx->q_data[V4L2_M2M_DST].bytesperline = max_w;
		ctx->q_data[V4L2_M2M_DST].sizeimage = usize;
	}
	ctx->q_data[V4L2_M2M_SRC].rect.width = max_w;
	ctx->q_data[V4L2_M2M_SRC].rect.height = max_h;
	ctx->q_data[V4L2_M2M_DST].rect.width = max_w;
	ctx->q_data[V4L2_M2M_DST].rect.height = max_h;

	/*
	 * Since the RBC2AXI logic only supports a single chroma plane,
	 * macroblock tiling only works for to NV12 pixel format.
	 */
	ctx->tiled_map_type = GDI_LINEAR_FRAME_MAP;
}
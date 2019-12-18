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
struct device {int dummy; } ;
struct bdisp_op_cfg {int wide; int src_interlaced; int src_yuv; int src_420; int dst_yuv; int dst_420; int cconv; int h_inc; int v_inc; int scale; int /*<<< orphan*/  dst_nbp; int /*<<< orphan*/  src_nbp; int /*<<< orphan*/  vflip; int /*<<< orphan*/  hflip; } ;
struct bdisp_frame {int width; scalar_t__ field; TYPE_2__* fmt; } ;
struct bdisp_ctx {int /*<<< orphan*/  vflip; int /*<<< orphan*/  hflip; struct bdisp_frame dst; struct bdisp_frame src; TYPE_1__* bdisp_dev; } ;
struct TYPE_4__ {scalar_t__ pixelformat; int /*<<< orphan*/  nb_planes; } ;
struct TYPE_3__ {struct device* dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int MAX_SRC_WIDTH ; 
 int MAX_VERTICAL_STRIDES ; 
 scalar_t__ V4L2_FIELD_INTERLACED ; 
 scalar_t__ V4L2_PIX_FMT_NV12 ; 
 scalar_t__ V4L2_PIX_FMT_YUV420 ; 
 scalar_t__ bdisp_hw_get_hv_inc (struct bdisp_ctx*,int*,int*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 

__attribute__((used)) static int bdisp_hw_get_op_cfg(struct bdisp_ctx *ctx, struct bdisp_op_cfg *c)
{
	struct device *dev = ctx->bdisp_dev->dev;
	struct bdisp_frame *src = &ctx->src;
	struct bdisp_frame *dst = &ctx->dst;

	if (src->width > MAX_SRC_WIDTH * MAX_VERTICAL_STRIDES) {
		dev_err(dev, "Image width out of HW caps\n");
		return -EINVAL;
	}

	c->wide = src->width > MAX_SRC_WIDTH;

	c->hflip = ctx->hflip;
	c->vflip = ctx->vflip;

	c->src_interlaced = (src->field == V4L2_FIELD_INTERLACED);

	c->src_nbp = src->fmt->nb_planes;
	c->src_yuv = (src->fmt->pixelformat == V4L2_PIX_FMT_NV12) ||
			(src->fmt->pixelformat == V4L2_PIX_FMT_YUV420);
	c->src_420 = c->src_yuv;

	c->dst_nbp = dst->fmt->nb_planes;
	c->dst_yuv = (dst->fmt->pixelformat == V4L2_PIX_FMT_NV12) ||
			(dst->fmt->pixelformat == V4L2_PIX_FMT_YUV420);
	c->dst_420 = c->dst_yuv;

	c->cconv = (c->src_yuv != c->dst_yuv);

	if (bdisp_hw_get_hv_inc(ctx, &c->h_inc, &c->v_inc)) {
		dev_err(dev, "Scale factor out of HW caps\n");
		return -EINVAL;
	}

	/* Deinterlacing adjustment : stretch a field to a frame */
	if (c->src_interlaced)
		c->v_inc /= 2;

	if ((c->h_inc != (1 << 10)) || (c->v_inc != (1 << 10)))
		c->scale = true;
	else
		c->scale = false;

	return 0;
}
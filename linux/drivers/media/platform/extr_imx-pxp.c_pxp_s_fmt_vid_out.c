#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  quantization; int /*<<< orphan*/  ycbcr_enc; int /*<<< orphan*/  xfer_func; int /*<<< orphan*/  colorspace; } ;
struct TYPE_6__ {TYPE_1__ pix; } ;
struct v4l2_format {TYPE_2__ fmt; } ;
struct pxp_ctx {TYPE_4__* q_data; int /*<<< orphan*/  xfer_func; int /*<<< orphan*/  colorspace; } ;
struct file {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  quant; int /*<<< orphan*/  ycbcr_enc; TYPE_3__* fmt; } ;
struct TYPE_7__ {int /*<<< orphan*/  fourcc; } ;

/* Variables and functions */
 size_t V4L2_M2M_DST ; 
 size_t V4L2_M2M_SRC ; 
 struct pxp_ctx* file2ctx (struct file*) ; 
 int /*<<< orphan*/  pxp_fixup_colorimetry_cap (struct pxp_ctx*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int pxp_s_fmt (struct pxp_ctx*,struct v4l2_format*) ; 
 int pxp_try_fmt_vid_out (struct file*,void*,struct v4l2_format*) ; 

__attribute__((used)) static int pxp_s_fmt_vid_out(struct file *file, void *priv,
			     struct v4l2_format *f)
{
	struct pxp_ctx *ctx = file2ctx(file);
	int ret;

	ret = pxp_try_fmt_vid_out(file, priv, f);
	if (ret)
		return ret;

	ret = pxp_s_fmt(file2ctx(file), f);
	if (ret)
		return ret;

	ctx->colorspace = f->fmt.pix.colorspace;
	ctx->xfer_func = f->fmt.pix.xfer_func;
	ctx->q_data[V4L2_M2M_SRC].ycbcr_enc = f->fmt.pix.ycbcr_enc;
	ctx->q_data[V4L2_M2M_SRC].quant = f->fmt.pix.quantization;

	pxp_fixup_colorimetry_cap(ctx, ctx->q_data[V4L2_M2M_DST].fmt->fourcc,
				  &ctx->q_data[V4L2_M2M_DST].ycbcr_enc,
				  &ctx->q_data[V4L2_M2M_DST].quant);

	return 0;
}
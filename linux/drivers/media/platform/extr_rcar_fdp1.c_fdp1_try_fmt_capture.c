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
struct v4l2_pix_format_mplane {int colorspace; int ycbcr_enc; int quantization; int height; int /*<<< orphan*/  width; int /*<<< orphan*/  xfer_func; int /*<<< orphan*/  field; int /*<<< orphan*/  num_planes; int /*<<< orphan*/  pixelformat; } ;
struct TYPE_2__ {int colorspace; int ycbcr_enc; int quantization; scalar_t__ field; int height; int /*<<< orphan*/  width; int /*<<< orphan*/  xfer_func; } ;
struct fdp1_q_data {TYPE_1__ format; } ;
struct fdp1_fmt {int /*<<< orphan*/  num_planes; int /*<<< orphan*/  fourcc; } ;
struct fdp1_ctx {struct fdp1_q_data out_q; } ;
typedef  enum v4l2_ycbcr_encoding { ____Placeholder_v4l2_ycbcr_encoding } v4l2_ycbcr_encoding ;
typedef  enum v4l2_quantization { ____Placeholder_v4l2_quantization } v4l2_quantization ;
typedef  enum v4l2_colorspace { ____Placeholder_v4l2_colorspace } v4l2_colorspace ;

/* Variables and functions */
 scalar_t__ V4L2_FIELD_ALTERNATE ; 
 int /*<<< orphan*/  V4L2_FIELD_NONE ; 
 int V4L2_MAP_QUANTIZATION_DEFAULT (int,int,int) ; 
 int V4L2_MAP_YCBCR_ENC_DEFAULT (int) ; 
 int /*<<< orphan*/  V4L2_PIX_FMT_YUYV ; 
 int V4L2_QUANTIZATION_DEFAULT ; 
 int V4L2_QUANTIZATION_LIM_RANGE ; 
 int V4L2_YCBCR_ENC_601 ; 
 int V4L2_YCBCR_ENC_709 ; 
 int V4L2_YCBCR_ENC_DEFAULT ; 
 int /*<<< orphan*/  fdp1_compute_stride (struct v4l2_pix_format_mplane*,struct fdp1_fmt const*) ; 
 struct fdp1_fmt* fdp1_find_format (int /*<<< orphan*/ ) ; 
 scalar_t__ fdp1_fmt_is_rgb (struct fdp1_fmt const*) ; 

__attribute__((used)) static void fdp1_try_fmt_capture(struct fdp1_ctx *ctx,
				 const struct fdp1_fmt **fmtinfo,
				 struct v4l2_pix_format_mplane *pix)
{
	struct fdp1_q_data *src_data = &ctx->out_q;
	enum v4l2_colorspace colorspace;
	enum v4l2_ycbcr_encoding ycbcr_enc;
	enum v4l2_quantization quantization;
	const struct fdp1_fmt *fmt;
	bool allow_rgb;

	/*
	 * Validate the pixel format. We can only accept RGB output formats if
	 * the input encoding and quantization are compatible with the format
	 * conversions supported by the hardware. The supported combinations are
	 *
	 * V4L2_YCBCR_ENC_601 + V4L2_QUANTIZATION_LIM_RANGE
	 * V4L2_YCBCR_ENC_601 + V4L2_QUANTIZATION_FULL_RANGE
	 * V4L2_YCBCR_ENC_709 + V4L2_QUANTIZATION_LIM_RANGE
	 */
	colorspace = src_data->format.colorspace;

	ycbcr_enc = src_data->format.ycbcr_enc;
	if (ycbcr_enc == V4L2_YCBCR_ENC_DEFAULT)
		ycbcr_enc = V4L2_MAP_YCBCR_ENC_DEFAULT(colorspace);

	quantization = src_data->format.quantization;
	if (quantization == V4L2_QUANTIZATION_DEFAULT)
		quantization = V4L2_MAP_QUANTIZATION_DEFAULT(false, colorspace,
							     ycbcr_enc);

	allow_rgb = ycbcr_enc == V4L2_YCBCR_ENC_601 ||
		    (ycbcr_enc == V4L2_YCBCR_ENC_709 &&
		     quantization == V4L2_QUANTIZATION_LIM_RANGE);

	fmt = fdp1_find_format(pix->pixelformat);
	if (!fmt || (!allow_rgb && fdp1_fmt_is_rgb(fmt)))
		fmt = fdp1_find_format(V4L2_PIX_FMT_YUYV);

	if (fmtinfo)
		*fmtinfo = fmt;

	pix->pixelformat = fmt->fourcc;
	pix->num_planes = fmt->num_planes;
	pix->field = V4L2_FIELD_NONE;

	/*
	 * The colorspace on the capture queue is copied from the output queue
	 * as the hardware can't change the colorspace. It can convert YCbCr to
	 * RGB though, in which case the encoding and quantization are set to
	 * default values as anything else wouldn't make sense.
	 */
	pix->colorspace = src_data->format.colorspace;
	pix->xfer_func = src_data->format.xfer_func;

	if (fdp1_fmt_is_rgb(fmt)) {
		pix->ycbcr_enc = V4L2_YCBCR_ENC_DEFAULT;
		pix->quantization = V4L2_QUANTIZATION_DEFAULT;
	} else {
		pix->ycbcr_enc = src_data->format.ycbcr_enc;
		pix->quantization = src_data->format.quantization;
	}

	/*
	 * The frame width is identical to the output queue, and the height is
	 * either doubled or identical depending on whether the output queue
	 * field order contains one or two fields per frame.
	 */
	pix->width = src_data->format.width;
	if (src_data->format.field == V4L2_FIELD_ALTERNATE)
		pix->height = 2 * src_data->format.height;
	else
		pix->height = src_data->format.height;

	fdp1_compute_stride(pix, fmt);
}
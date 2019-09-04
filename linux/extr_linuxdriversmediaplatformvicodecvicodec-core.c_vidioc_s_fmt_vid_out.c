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
struct vicodec_ctx {int /*<<< orphan*/  quantization; int /*<<< orphan*/  ycbcr_enc; int /*<<< orphan*/  xfer_func; int /*<<< orphan*/  colorspace; } ;
struct v4l2_pix_format_mplane {int /*<<< orphan*/  quantization; int /*<<< orphan*/  ycbcr_enc; int /*<<< orphan*/  xfer_func; int /*<<< orphan*/  colorspace; } ;
struct v4l2_pix_format {int /*<<< orphan*/  quantization; int /*<<< orphan*/  ycbcr_enc; int /*<<< orphan*/  xfer_func; int /*<<< orphan*/  colorspace; } ;
struct TYPE_2__ {struct v4l2_pix_format_mplane pix_mp; struct v4l2_pix_format pix; } ;
struct v4l2_format {int type; TYPE_1__ fmt; } ;
struct file {int dummy; } ;

/* Variables and functions */
#define  V4L2_BUF_TYPE_VIDEO_CAPTURE 131 
#define  V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE 130 
#define  V4L2_BUF_TYPE_VIDEO_OUTPUT 129 
#define  V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE 128 
 struct vicodec_ctx* file2ctx (struct file*) ; 
 int vidioc_s_fmt (struct vicodec_ctx*,struct v4l2_format*) ; 
 int vidioc_try_fmt_vid_out (struct file*,void*,struct v4l2_format*) ; 

__attribute__((used)) static int vidioc_s_fmt_vid_out(struct file *file, void *priv,
				struct v4l2_format *f)
{
	struct vicodec_ctx *ctx = file2ctx(file);
	struct v4l2_pix_format_mplane *pix_mp;
	struct v4l2_pix_format *pix;
	int ret;

	ret = vidioc_try_fmt_vid_out(file, priv, f);
	if (ret)
		return ret;

	ret = vidioc_s_fmt(file2ctx(file), f);
	if (!ret) {
		switch (f->type) {
		case V4L2_BUF_TYPE_VIDEO_CAPTURE:
		case V4L2_BUF_TYPE_VIDEO_OUTPUT:
			pix = &f->fmt.pix;
			ctx->colorspace = pix->colorspace;
			ctx->xfer_func = pix->xfer_func;
			ctx->ycbcr_enc = pix->ycbcr_enc;
			ctx->quantization = pix->quantization;
			break;
		case V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE:
		case V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE:
			pix_mp = &f->fmt.pix_mp;
			ctx->colorspace = pix_mp->colorspace;
			ctx->xfer_func = pix_mp->xfer_func;
			ctx->ycbcr_enc = pix_mp->ycbcr_enc;
			ctx->quantization = pix_mp->quantization;
			break;
		default:
			break;
		}
	}
	return ret;
}
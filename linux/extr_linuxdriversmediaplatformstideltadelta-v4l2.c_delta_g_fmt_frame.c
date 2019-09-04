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
struct v4l2_pix_format {int /*<<< orphan*/  quantization; int /*<<< orphan*/  ycbcr_enc; int /*<<< orphan*/  xfer_func; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  sizeimage; int /*<<< orphan*/  bytesperline; int /*<<< orphan*/  field; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  pixelformat; } ;
struct TYPE_2__ {struct v4l2_pix_format pix; } ;
struct v4l2_format {TYPE_1__ fmt; } ;
struct file {int /*<<< orphan*/  private_data; } ;
struct delta_streaminfo {int /*<<< orphan*/  quantization; int /*<<< orphan*/  ycbcr_enc; int /*<<< orphan*/  xfer_func; int /*<<< orphan*/  colorspace; } ;
struct delta_frameinfo {int /*<<< orphan*/  quantization; int /*<<< orphan*/  ycbcr_enc; int /*<<< orphan*/  xfer_func; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  size; int /*<<< orphan*/  pixelformat; int /*<<< orphan*/  aligned_width; int /*<<< orphan*/  field; int /*<<< orphan*/  aligned_height; } ;
struct delta_dev {int /*<<< orphan*/  dev; } ;
struct delta_ctx {int flags; int /*<<< orphan*/  name; struct delta_streaminfo streaminfo; struct delta_frameinfo frameinfo; struct delta_dev* dev; } ;
typedef  int /*<<< orphan*/  str ;

/* Variables and functions */
 int DELTA_FLAG_FRAMEINFO ; 
 int DELTA_FLAG_STREAMINFO ; 
 int /*<<< orphan*/  delta_frameinfo_str (struct delta_frameinfo*,unsigned char*,int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  frame_stride (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct delta_ctx* to_ctx (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int delta_g_fmt_frame(struct file *file, void *fh, struct v4l2_format *f)
{
	struct delta_ctx *ctx = to_ctx(file->private_data);
	struct delta_dev *delta = ctx->dev;
	struct v4l2_pix_format *pix = &f->fmt.pix;
	struct delta_frameinfo *frameinfo = &ctx->frameinfo;
	struct delta_streaminfo *streaminfo = &ctx->streaminfo;
	unsigned char str[100] = "";

	if (!(ctx->flags & DELTA_FLAG_FRAMEINFO))
		dev_dbg(delta->dev,
			"%s V4L2 GET_FMT (CAPTURE): no frame information available, default to %s\n",
			ctx->name,
			delta_frameinfo_str(frameinfo, str, sizeof(str)));

	pix->pixelformat = frameinfo->pixelformat;
	pix->width = frameinfo->aligned_width;
	pix->height = frameinfo->aligned_height;
	pix->field = frameinfo->field;
	pix->bytesperline = frame_stride(frameinfo->aligned_width,
					       frameinfo->pixelformat);
	pix->sizeimage = frameinfo->size;

	if (ctx->flags & DELTA_FLAG_STREAMINFO) {
		/* align colorspace & friends on stream ones if any set */
		frameinfo->colorspace = streaminfo->colorspace;
		frameinfo->xfer_func = streaminfo->xfer_func;
		frameinfo->ycbcr_enc = streaminfo->ycbcr_enc;
		frameinfo->quantization = streaminfo->quantization;
	}
	pix->colorspace = frameinfo->colorspace;
	pix->xfer_func = frameinfo->xfer_func;
	pix->ycbcr_enc = frameinfo->ycbcr_enc;
	pix->quantization = frameinfo->quantization;

	return 0;
}
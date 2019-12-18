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
struct v4l2_pix_format {int /*<<< orphan*/  quantization; int /*<<< orphan*/  ycbcr_enc; int /*<<< orphan*/  xfer_func; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  sizeimage; scalar_t__ bytesperline; int /*<<< orphan*/  field; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  pixelformat; } ;
struct TYPE_2__ {struct v4l2_pix_format pix; } ;
struct v4l2_format {TYPE_1__ fmt; } ;
struct file {int /*<<< orphan*/  private_data; } ;
struct delta_streaminfo {int /*<<< orphan*/  quantization; int /*<<< orphan*/  ycbcr_enc; int /*<<< orphan*/  xfer_func; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  field; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  streamformat; } ;
struct delta_dev {int /*<<< orphan*/  dev; } ;
struct delta_ctx {int flags; int /*<<< orphan*/  max_au_size; int /*<<< orphan*/  name; struct delta_streaminfo streaminfo; struct delta_dev* dev; } ;
typedef  int /*<<< orphan*/  str ;

/* Variables and functions */
 int DELTA_FLAG_STREAMINFO ; 
 int /*<<< orphan*/  delta_streaminfo_str (struct delta_streaminfo*,unsigned char*,int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct delta_ctx* to_ctx (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int delta_g_fmt_stream(struct file *file, void *fh,
			      struct v4l2_format *f)
{
	struct delta_ctx *ctx = to_ctx(file->private_data);
	struct delta_dev *delta = ctx->dev;
	struct v4l2_pix_format *pix = &f->fmt.pix;
	struct delta_streaminfo *streaminfo = &ctx->streaminfo;
	unsigned char str[100] = "";

	if (!(ctx->flags & DELTA_FLAG_STREAMINFO))
		dev_dbg(delta->dev,
			"%s V4L2 GET_FMT (OUTPUT): no stream information available, default to %s\n",
			ctx->name,
			delta_streaminfo_str(streaminfo, str, sizeof(str)));

	pix->pixelformat = streaminfo->streamformat;
	pix->width = streaminfo->width;
	pix->height = streaminfo->height;
	pix->field = streaminfo->field;
	pix->bytesperline = 0;
	pix->sizeimage = ctx->max_au_size;
	pix->colorspace = streaminfo->colorspace;
	pix->xfer_func = streaminfo->xfer_func;
	pix->ycbcr_enc = streaminfo->ycbcr_enc;
	pix->quantization = streaminfo->quantization;

	return 0;
}
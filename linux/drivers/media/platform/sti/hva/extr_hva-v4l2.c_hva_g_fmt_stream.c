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
struct TYPE_3__ {int /*<<< orphan*/  sizeimage; scalar_t__ bytesperline; int /*<<< orphan*/  pixelformat; int /*<<< orphan*/  quantization; int /*<<< orphan*/  ycbcr_enc; int /*<<< orphan*/  xfer_func; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  field; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_4__ {TYPE_1__ pix; } ;
struct v4l2_format {TYPE_2__ fmt; } ;
struct hva_streaminfo {int /*<<< orphan*/  streamformat; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct hva_ctx {int /*<<< orphan*/  max_stream_size; int /*<<< orphan*/  quantization; int /*<<< orphan*/  ycbcr_enc; int /*<<< orphan*/  xfer_func; int /*<<< orphan*/  colorspace; struct hva_streaminfo streaminfo; } ;
struct file {int /*<<< orphan*/  private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_FIELD_NONE ; 
 struct hva_ctx* fh_to_ctx (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hva_g_fmt_stream(struct file *file, void *fh, struct v4l2_format *f)
{
	struct hva_ctx *ctx = fh_to_ctx(file->private_data);
	struct hva_streaminfo *streaminfo = &ctx->streaminfo;

	f->fmt.pix.width = streaminfo->width;
	f->fmt.pix.height = streaminfo->height;
	f->fmt.pix.field = V4L2_FIELD_NONE;
	f->fmt.pix.colorspace = ctx->colorspace;
	f->fmt.pix.xfer_func = ctx->xfer_func;
	f->fmt.pix.ycbcr_enc = ctx->ycbcr_enc;
	f->fmt.pix.quantization = ctx->quantization;
	f->fmt.pix.pixelformat = streaminfo->streamformat;
	f->fmt.pix.bytesperline = 0;
	f->fmt.pix.sizeimage = ctx->max_stream_size;

	return 0;
}
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
struct TYPE_3__ {int /*<<< orphan*/  sizeimage; int /*<<< orphan*/  bytesperline; int /*<<< orphan*/  pixelformat; int /*<<< orphan*/  quantization; int /*<<< orphan*/  ycbcr_enc; int /*<<< orphan*/  xfer_func; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  field; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_4__ {TYPE_1__ pix; } ;
struct v4l2_format {TYPE_2__ fmt; } ;
struct hva_frameinfo {int /*<<< orphan*/  size; int /*<<< orphan*/  pixelformat; int /*<<< orphan*/  aligned_width; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct hva_ctx {int /*<<< orphan*/  quantization; int /*<<< orphan*/  ycbcr_enc; int /*<<< orphan*/  xfer_func; int /*<<< orphan*/  colorspace; struct hva_frameinfo frameinfo; } ;
struct file {int /*<<< orphan*/  private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_FIELD_NONE ; 
 struct hva_ctx* fh_to_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  frame_stride (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hva_g_fmt_frame(struct file *file, void *fh, struct v4l2_format *f)
{
	struct hva_ctx *ctx = fh_to_ctx(file->private_data);
	struct hva_frameinfo *frameinfo = &ctx->frameinfo;

	f->fmt.pix.width = frameinfo->width;
	f->fmt.pix.height = frameinfo->height;
	f->fmt.pix.field = V4L2_FIELD_NONE;
	f->fmt.pix.colorspace = ctx->colorspace;
	f->fmt.pix.xfer_func = ctx->xfer_func;
	f->fmt.pix.ycbcr_enc = ctx->ycbcr_enc;
	f->fmt.pix.quantization = ctx->quantization;
	f->fmt.pix.pixelformat = frameinfo->pixelformat;
	f->fmt.pix.bytesperline = frame_stride(frameinfo->aligned_width,
					       frameinfo->pixelformat);
	f->fmt.pix.sizeimage = frameinfo->size;

	return 0;
}
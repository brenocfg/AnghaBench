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
struct v4l2_pix_format {int /*<<< orphan*/  colorspace; int /*<<< orphan*/  sizeimage; int /*<<< orphan*/  bytesperline; int /*<<< orphan*/  field; int /*<<< orphan*/  pixelformat; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_6__ {struct v4l2_pix_format pix; } ;
struct v4l2_format {int /*<<< orphan*/  type; TYPE_2__ fmt; } ;
struct file {int dummy; } ;
struct bdisp_frame {int /*<<< orphan*/  colorspace; int /*<<< orphan*/  sizeimage; int /*<<< orphan*/  bytesperline; int /*<<< orphan*/  field; TYPE_3__* fmt; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct bdisp_ctx {TYPE_1__* bdisp_dev; } ;
struct TYPE_8__ {int /*<<< orphan*/  colorspace; } ;
struct TYPE_7__ {int /*<<< orphan*/  pixelformat; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct bdisp_frame*) ; 
 int PTR_ERR (struct bdisp_frame*) ; 
 int /*<<< orphan*/  V4L2_BUF_TYPE_VIDEO_OUTPUT ; 
 TYPE_4__ bdisp_dflt_fmt ; 
 struct bdisp_frame* ctx_get_frame (struct bdisp_ctx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,struct bdisp_frame*) ; 
 struct bdisp_ctx* fh_to_ctx (void*) ; 

__attribute__((used)) static int bdisp_g_fmt(struct file *file, void *fh, struct v4l2_format *f)
{
	struct bdisp_ctx *ctx = fh_to_ctx(fh);
	struct v4l2_pix_format *pix;
	struct bdisp_frame *frame  = ctx_get_frame(ctx, f->type);

	if (IS_ERR(frame)) {
		dev_err(ctx->bdisp_dev->dev, "Invalid frame (%p)\n", frame);
		return PTR_ERR(frame);
	}

	pix = &f->fmt.pix;
	pix->width = frame->width;
	pix->height = frame->height;
	pix->pixelformat = frame->fmt->pixelformat;
	pix->field = frame->field;
	pix->bytesperline = frame->bytesperline;
	pix->sizeimage = frame->sizeimage;
	pix->colorspace = (f->type == V4L2_BUF_TYPE_VIDEO_OUTPUT) ?
				frame->colorspace : bdisp_dflt_fmt.colorspace;

	return 0;
}
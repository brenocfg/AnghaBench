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
struct venus_inst {int reconfig; int /*<<< orphan*/  out_height; int /*<<< orphan*/  out_width; int /*<<< orphan*/  xfer_func; int /*<<< orphan*/  quantization; int /*<<< orphan*/  ycbcr_enc; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  height; int /*<<< orphan*/  width; struct venus_format* fmt_cap; int /*<<< orphan*/  reconfig_height; int /*<<< orphan*/  reconfig_width; struct venus_format* fmt_out; } ;
struct venus_format {int /*<<< orphan*/  pixfmt; } ;
struct v4l2_pix_format_mplane {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  xfer_func; int /*<<< orphan*/  quantization; int /*<<< orphan*/  ycbcr_enc; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  pixelformat; } ;
struct TYPE_2__ {struct v4l2_pix_format_mplane pix_mp; } ;
struct v4l2_format {scalar_t__ type; TYPE_1__ fmt; } ;
struct file {int dummy; } ;

/* Variables and functions */
 scalar_t__ V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE ; 
 struct venus_inst* to_inst (struct file*) ; 
 int /*<<< orphan*/  vdec_try_fmt_common (struct venus_inst*,struct v4l2_format*) ; 

__attribute__((used)) static int vdec_g_fmt(struct file *file, void *fh, struct v4l2_format *f)
{
	struct venus_inst *inst = to_inst(file);
	const struct venus_format *fmt = NULL;
	struct v4l2_pix_format_mplane *pixmp = &f->fmt.pix_mp;

	if (f->type == V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE)
		fmt = inst->fmt_cap;
	else if (f->type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE)
		fmt = inst->fmt_out;

	if (inst->reconfig) {
		struct v4l2_format format = {};

		inst->out_width = inst->reconfig_width;
		inst->out_height = inst->reconfig_height;
		inst->reconfig = false;

		format.type = V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE;
		format.fmt.pix_mp.pixelformat = inst->fmt_cap->pixfmt;
		format.fmt.pix_mp.width = inst->out_width;
		format.fmt.pix_mp.height = inst->out_height;

		vdec_try_fmt_common(inst, &format);

		inst->width = format.fmt.pix_mp.width;
		inst->height = format.fmt.pix_mp.height;
	}

	pixmp->pixelformat = fmt->pixfmt;

	if (f->type == V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE) {
		pixmp->width = inst->width;
		pixmp->height = inst->height;
		pixmp->colorspace = inst->colorspace;
		pixmp->ycbcr_enc = inst->ycbcr_enc;
		pixmp->quantization = inst->quantization;
		pixmp->xfer_func = inst->xfer_func;
	} else if (f->type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE) {
		pixmp->width = inst->out_width;
		pixmp->height = inst->out_height;
	}

	vdec_try_fmt_common(inst, f);

	return 0;
}
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
struct v4l2_pix_format_mplane {TYPE_4__* plane_fmt; int /*<<< orphan*/  num_planes; int /*<<< orphan*/  pixelformat; void* field; scalar_t__ height; scalar_t__ width; } ;
struct TYPE_5__ {struct v4l2_pix_format_mplane pix_mp; } ;
struct v4l2_format {scalar_t__ type; TYPE_1__ fmt; } ;
struct s5p_mfc_ctx {int /*<<< orphan*/  chroma_size; int /*<<< orphan*/  buf_width; int /*<<< orphan*/  luma_size; TYPE_3__* src_fmt; scalar_t__ img_height; scalar_t__ img_width; int /*<<< orphan*/  enc_dst_buf_size; TYPE_2__* dst_fmt; int /*<<< orphan*/  state; } ;
struct file {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  sizeimage; int /*<<< orphan*/  bytesperline; } ;
struct TYPE_7__ {int /*<<< orphan*/  num_planes; int /*<<< orphan*/  fourcc; } ;
struct TYPE_6__ {int /*<<< orphan*/  num_planes; int /*<<< orphan*/  fourcc; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE ; 
 void* V4L2_FIELD_NONE ; 
 struct s5p_mfc_ctx* fh_to_ctx (void*) ; 
 int /*<<< orphan*/  mfc_debug (int,char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mfc_err (char*) ; 

__attribute__((used)) static int vidioc_g_fmt(struct file *file, void *priv, struct v4l2_format *f)
{
	struct s5p_mfc_ctx *ctx = fh_to_ctx(priv);
	struct v4l2_pix_format_mplane *pix_fmt_mp = &f->fmt.pix_mp;

	mfc_debug(2, "f->type = %d ctx->state = %d\n", f->type, ctx->state);
	if (f->type == V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE) {
		/* This is run on output (encoder dest) */
		pix_fmt_mp->width = 0;
		pix_fmt_mp->height = 0;
		pix_fmt_mp->field = V4L2_FIELD_NONE;
		pix_fmt_mp->pixelformat = ctx->dst_fmt->fourcc;
		pix_fmt_mp->num_planes = ctx->dst_fmt->num_planes;

		pix_fmt_mp->plane_fmt[0].bytesperline = ctx->enc_dst_buf_size;
		pix_fmt_mp->plane_fmt[0].sizeimage = ctx->enc_dst_buf_size;
	} else if (f->type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE) {
		/* This is run on capture (encoder src) */
		pix_fmt_mp->width = ctx->img_width;
		pix_fmt_mp->height = ctx->img_height;

		pix_fmt_mp->field = V4L2_FIELD_NONE;
		pix_fmt_mp->pixelformat = ctx->src_fmt->fourcc;
		pix_fmt_mp->num_planes = ctx->src_fmt->num_planes;

		pix_fmt_mp->plane_fmt[0].bytesperline = ctx->buf_width;
		pix_fmt_mp->plane_fmt[0].sizeimage = ctx->luma_size;
		pix_fmt_mp->plane_fmt[1].bytesperline = ctx->buf_width;
		pix_fmt_mp->plane_fmt[1].sizeimage = ctx->chroma_size;
	} else {
		mfc_err("invalid buf type\n");
		return -EINVAL;
	}
	return 0;
}
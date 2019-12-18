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
struct vicodec_ctx {scalar_t__ is_stateless; } ;
struct v4l2_plane_pix_format {int bytesperline; int sizeimage; int /*<<< orphan*/  reserved; } ;
struct v4l2_pix_format_mplane {int num_planes; int width; int height; int /*<<< orphan*/  reserved; int /*<<< orphan*/  pixelformat; void* field; struct v4l2_plane_pix_format* plane_fmt; } ;
struct v4l2_pix_format {int width; int height; int bytesperline; int sizeimage; int /*<<< orphan*/  pixelformat; void* field; } ;
struct v4l2_fwht_pixfmt_info {int bytesperline_mult; int sizeimage_mult; int sizeimage_div; int /*<<< orphan*/  height_div; int /*<<< orphan*/  width_div; } ;
struct TYPE_2__ {struct v4l2_pix_format_mplane pix_mp; struct v4l2_pix_format pix; } ;
struct v4l2_format {int type; TYPE_1__ fmt; } ;
struct fwht_cframe_hdr {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MAX_HEIGHT ; 
 int /*<<< orphan*/  MAX_WIDTH ; 
 int /*<<< orphan*/  MIN_HEIGHT ; 
 int /*<<< orphan*/  MIN_WIDTH ; 
#define  V4L2_BUF_TYPE_VIDEO_CAPTURE 131 
#define  V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE 130 
#define  V4L2_BUF_TYPE_VIDEO_OUTPUT 129 
#define  V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE 128 
 void* V4L2_FIELD_NONE ; 
 int /*<<< orphan*/  V4L2_PIX_FMT_FWHT ; 
 int /*<<< orphan*/  V4L2_PIX_FMT_FWHT_STATELESS ; 
 void* clamp (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct v4l2_fwht_pixfmt_info* find_fmt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct v4l2_fwht_pixfmt_info pixfmt_fwht ; 
 struct v4l2_fwht_pixfmt_info pixfmt_stateless_fwht ; 
 void* vic_round_dim (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vidioc_try_fmt(struct vicodec_ctx *ctx, struct v4l2_format *f)
{
	struct v4l2_pix_format_mplane *pix_mp;
	struct v4l2_pix_format *pix;
	struct v4l2_plane_pix_format *plane;
	const struct v4l2_fwht_pixfmt_info *info = ctx->is_stateless ?
		&pixfmt_stateless_fwht : &pixfmt_fwht;

	switch (f->type) {
	case V4L2_BUF_TYPE_VIDEO_CAPTURE:
	case V4L2_BUF_TYPE_VIDEO_OUTPUT:
		pix = &f->fmt.pix;
		if (pix->pixelformat != V4L2_PIX_FMT_FWHT &&
		    pix->pixelformat != V4L2_PIX_FMT_FWHT_STATELESS)
			info = find_fmt(pix->pixelformat);

		pix->width = clamp(pix->width, MIN_WIDTH, MAX_WIDTH);
		pix->width = vic_round_dim(pix->width, info->width_div);

		pix->height = clamp(pix->height, MIN_HEIGHT, MAX_HEIGHT);
		pix->height = vic_round_dim(pix->height, info->height_div);

		pix->field = V4L2_FIELD_NONE;
		pix->bytesperline =
			pix->width * info->bytesperline_mult;
		pix->sizeimage = pix->width * pix->height *
			info->sizeimage_mult / info->sizeimage_div;
		if (pix->pixelformat == V4L2_PIX_FMT_FWHT)
			pix->sizeimage += sizeof(struct fwht_cframe_hdr);
		break;
	case V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE:
	case V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE:
		pix_mp = &f->fmt.pix_mp;
		plane = pix_mp->plane_fmt;
		if (pix_mp->pixelformat != V4L2_PIX_FMT_FWHT &&
		    pix_mp->pixelformat != V4L2_PIX_FMT_FWHT_STATELESS)
			info = find_fmt(pix_mp->pixelformat);
		pix_mp->num_planes = 1;

		pix_mp->width = clamp(pix_mp->width, MIN_WIDTH, MAX_WIDTH);
		pix_mp->width = vic_round_dim(pix_mp->width, info->width_div);

		pix_mp->height = clamp(pix_mp->height, MIN_HEIGHT, MAX_HEIGHT);
		pix_mp->height = vic_round_dim(pix_mp->height,
					       info->height_div);

		pix_mp->field = V4L2_FIELD_NONE;
		plane->bytesperline =
			pix_mp->width * info->bytesperline_mult;
		plane->sizeimage = pix_mp->width * pix_mp->height *
			info->sizeimage_mult / info->sizeimage_div;
		if (pix_mp->pixelformat == V4L2_PIX_FMT_FWHT)
			plane->sizeimage += sizeof(struct fwht_cframe_hdr);
		memset(pix_mp->reserved, 0, sizeof(pix_mp->reserved));
		memset(plane->reserved, 0, sizeof(plane->reserved));
		break;
	default:
		return -EINVAL;
	}

	return 0;
}
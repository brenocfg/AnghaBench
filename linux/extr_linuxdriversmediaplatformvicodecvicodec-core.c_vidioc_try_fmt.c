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
struct vicodec_ctx {int dummy; } ;
struct v4l2_pix_format_mplane {int width; int height; int num_planes; TYPE_2__* plane_fmt; int /*<<< orphan*/  reserved; int /*<<< orphan*/  pixelformat; void* field; } ;
struct v4l2_pix_format {int width; int height; int bytesperline; int sizeimage; int /*<<< orphan*/  pixelformat; void* field; } ;
struct TYPE_3__ {struct v4l2_pix_format_mplane pix_mp; struct v4l2_pix_format pix; } ;
struct v4l2_format {int type; TYPE_1__ fmt; } ;
struct cframe_hdr {int dummy; } ;
struct TYPE_4__ {int bytesperline; int sizeimage; int /*<<< orphan*/  reserved; } ;

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
 int clamp (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int vidioc_try_fmt(struct vicodec_ctx *ctx, struct v4l2_format *f)
{
	struct v4l2_pix_format_mplane *pix_mp;
	struct v4l2_pix_format *pix;

	switch (f->type) {
	case V4L2_BUF_TYPE_VIDEO_CAPTURE:
	case V4L2_BUF_TYPE_VIDEO_OUTPUT:
		pix = &f->fmt.pix;
		pix->width = clamp(pix->width, MIN_WIDTH, MAX_WIDTH) & ~7;
		pix->height = clamp(pix->height, MIN_HEIGHT, MAX_HEIGHT) & ~7;
		pix->bytesperline = pix->width;
		pix->sizeimage = pix->width * pix->height * 3 / 2;
		pix->field = V4L2_FIELD_NONE;
		if (pix->pixelformat == V4L2_PIX_FMT_FWHT) {
			pix->bytesperline = 0;
			pix->sizeimage += sizeof(struct cframe_hdr);
		}
		break;
	case V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE:
	case V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE:
		pix_mp = &f->fmt.pix_mp;
		pix_mp->width = clamp(pix_mp->width, MIN_WIDTH, MAX_WIDTH) & ~7;
		pix_mp->height =
			clamp(pix_mp->height, MIN_HEIGHT, MAX_HEIGHT) & ~7;
		pix_mp->plane_fmt[0].bytesperline = pix_mp->width;
		pix_mp->plane_fmt[0].sizeimage =
			pix_mp->width * pix_mp->height * 3 / 2;
		pix_mp->field = V4L2_FIELD_NONE;
		pix_mp->num_planes = 1;
		if (pix_mp->pixelformat == V4L2_PIX_FMT_FWHT) {
			pix_mp->plane_fmt[0].bytesperline = 0;
			pix_mp->plane_fmt[0].sizeimage +=
					sizeof(struct cframe_hdr);
		}
		memset(pix_mp->reserved, 0, sizeof(pix_mp->reserved));
		memset(pix_mp->plane_fmt[0].reserved, 0,
		       sizeof(pix_mp->plane_fmt[0].reserved));
		break;
	default:
		return -EINVAL;
	}

	return 0;
}
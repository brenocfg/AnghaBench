#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct v4l2_pix_format {int height; int bytesperline; int sizeimage; int /*<<< orphan*/  pixelformat; int /*<<< orphan*/  width; int /*<<< orphan*/  field; int /*<<< orphan*/  colorspace; } ;
struct TYPE_4__ {struct v4l2_pix_format pix; } ;
struct v4l2_format {TYPE_1__ fmt; } ;
struct ivtv_open_id {scalar_t__ type; struct ivtv* itv; } ;
struct TYPE_6__ {int lace_mode; int v4l2_src_h; int /*<<< orphan*/  v4l2_src_w; } ;
struct TYPE_5__ {int height; int /*<<< orphan*/  width; } ;
struct ivtv {int v4l2_cap; TYPE_3__ yuv_info; TYPE_2__ main_rect; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IVTV_DEC_STREAM_TYPE_YUV ; 
#define  IVTV_YUV_MODE_INTERLACED 129 
 int IVTV_YUV_MODE_MASK ; 
#define  IVTV_YUV_MODE_PROGRESSIVE 128 
 int IVTV_YUV_SYNC_MASK ; 
 int V4L2_CAP_VIDEO_OUTPUT ; 
 int /*<<< orphan*/  V4L2_COLORSPACE_SMPTE170M ; 
 int /*<<< orphan*/  V4L2_FIELD_ANY ; 
 int /*<<< orphan*/  V4L2_FIELD_INTERLACED ; 
 int /*<<< orphan*/  V4L2_FIELD_INTERLACED_BT ; 
 int /*<<< orphan*/  V4L2_FIELD_INTERLACED_TB ; 
 int /*<<< orphan*/  V4L2_FIELD_NONE ; 
 int /*<<< orphan*/  V4L2_PIX_FMT_HM12 ; 
 int /*<<< orphan*/  V4L2_PIX_FMT_MPEG ; 
 struct ivtv_open_id* fh2id (void*) ; 

__attribute__((used)) static int ivtv_g_fmt_vid_out(struct file *file, void *fh, struct v4l2_format *fmt)
{
	struct ivtv_open_id *id = fh2id(fh);
	struct ivtv *itv = id->itv;
	struct v4l2_pix_format *pixfmt = &fmt->fmt.pix;

	if (!(itv->v4l2_cap & V4L2_CAP_VIDEO_OUTPUT))
		return -EINVAL;
	pixfmt->width = itv->main_rect.width;
	pixfmt->height = itv->main_rect.height;
	pixfmt->colorspace = V4L2_COLORSPACE_SMPTE170M;
	pixfmt->field = V4L2_FIELD_INTERLACED;
	if (id->type == IVTV_DEC_STREAM_TYPE_YUV) {
		switch (itv->yuv_info.lace_mode & IVTV_YUV_MODE_MASK) {
		case IVTV_YUV_MODE_INTERLACED:
			pixfmt->field = (itv->yuv_info.lace_mode & IVTV_YUV_SYNC_MASK) ?
				V4L2_FIELD_INTERLACED_BT : V4L2_FIELD_INTERLACED_TB;
			break;
		case IVTV_YUV_MODE_PROGRESSIVE:
			pixfmt->field = V4L2_FIELD_NONE;
			break;
		default:
			pixfmt->field = V4L2_FIELD_ANY;
			break;
		}
		pixfmt->pixelformat = V4L2_PIX_FMT_HM12;
		pixfmt->bytesperline = 720;
		pixfmt->width = itv->yuv_info.v4l2_src_w;
		pixfmt->height = itv->yuv_info.v4l2_src_h;
		/* YUV size is (Y=(h*w) + UV=(h*(w/2))) */
		pixfmt->sizeimage =
			1080 * ((pixfmt->height + 31) & ~31);
	} else {
		pixfmt->pixelformat = V4L2_PIX_FMT_MPEG;
		pixfmt->sizeimage = 128 * 1024;
		pixfmt->bytesperline = 0;
	}
	return 0;
}
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
typedef  int /*<<< orphan*/  u32 ;
struct v4l2_plane_pix_format {int sizeimage; int bytesperline; int /*<<< orphan*/  reserved; } ;
struct v4l2_pix_format_mplane {scalar_t__ pixelformat; int num_planes; scalar_t__ field; void* height; void* width; int /*<<< orphan*/  reserved; struct v4l2_plane_pix_format* plane_fmt; } ;
struct TYPE_4__ {struct v4l2_pix_format_mplane pix_mp; } ;
struct v4l2_format {scalar_t__ type; TYPE_1__ fmt; } ;
struct amvdec_session {struct amvdec_format* fmt_out; TYPE_3__* core; } ;
struct amvdec_format {scalar_t__* pixfmts_cap; int /*<<< orphan*/  max_height; int /*<<< orphan*/  max_width; } ;
struct TYPE_6__ {TYPE_2__* platform; } ;
struct TYPE_5__ {struct amvdec_format* formats; } ;

/* Variables and functions */
 int ALIGN (void*,int) ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE ; 
 scalar_t__ V4L2_FIELD_ANY ; 
 scalar_t__ V4L2_FIELD_NONE ; 
 scalar_t__ V4L2_PIX_FMT_MPEG2 ; 
 scalar_t__ V4L2_PIX_FMT_NV12M ; 
 scalar_t__ V4L2_PIX_FMT_YUV420M ; 
 void* clamp (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct amvdec_format* find_format (struct amvdec_format const*,int /*<<< orphan*/ ,scalar_t__) ; 
 int get_output_size (void*,void*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vdec_supports_pixfmt_cap (struct amvdec_format const*,scalar_t__) ; 

__attribute__((used)) static const struct amvdec_format *
vdec_try_fmt_common(struct amvdec_session *sess, u32 size,
		    struct v4l2_format *f)
{
	struct v4l2_pix_format_mplane *pixmp = &f->fmt.pix_mp;
	struct v4l2_plane_pix_format *pfmt = pixmp->plane_fmt;
	const struct amvdec_format *fmts = sess->core->platform->formats;
	const struct amvdec_format *fmt_out;

	memset(pfmt[0].reserved, 0, sizeof(pfmt[0].reserved));
	memset(pixmp->reserved, 0, sizeof(pixmp->reserved));

	if (f->type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE) {
		fmt_out = find_format(fmts, size, pixmp->pixelformat);
		if (!fmt_out) {
			pixmp->pixelformat = V4L2_PIX_FMT_MPEG2;
			fmt_out = find_format(fmts, size, pixmp->pixelformat);
		}

		pfmt[0].sizeimage =
			get_output_size(pixmp->width, pixmp->height);
		pfmt[0].bytesperline = 0;
		pixmp->num_planes = 1;
	} else if (f->type == V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE) {
		fmt_out = sess->fmt_out;
		if (!vdec_supports_pixfmt_cap(fmt_out, pixmp->pixelformat))
			pixmp->pixelformat = fmt_out->pixfmts_cap[0];

		memset(pfmt[1].reserved, 0, sizeof(pfmt[1].reserved));
		if (pixmp->pixelformat == V4L2_PIX_FMT_NV12M) {
			pfmt[0].sizeimage =
				get_output_size(pixmp->width, pixmp->height);
			pfmt[0].bytesperline = ALIGN(pixmp->width, 64);

			pfmt[1].sizeimage =
			      get_output_size(pixmp->width, pixmp->height) / 2;
			pfmt[1].bytesperline = ALIGN(pixmp->width, 64);
			pixmp->num_planes = 2;
		} else if (pixmp->pixelformat == V4L2_PIX_FMT_YUV420M) {
			pfmt[0].sizeimage =
				get_output_size(pixmp->width, pixmp->height);
			pfmt[0].bytesperline = ALIGN(pixmp->width, 64);

			pfmt[1].sizeimage =
			      get_output_size(pixmp->width, pixmp->height) / 4;
			pfmt[1].bytesperline = ALIGN(pixmp->width, 64) / 2;

			pfmt[2].sizeimage =
			      get_output_size(pixmp->width, pixmp->height) / 4;
			pfmt[2].bytesperline = ALIGN(pixmp->width, 64) / 2;
			pixmp->num_planes = 3;
		}
	} else {
		return NULL;
	}

	pixmp->width  = clamp(pixmp->width,  (u32)256, fmt_out->max_width);
	pixmp->height = clamp(pixmp->height, (u32)144, fmt_out->max_height);

	if (pixmp->field == V4L2_FIELD_ANY)
		pixmp->field = V4L2_FIELD_NONE;

	return fmt_out;
}
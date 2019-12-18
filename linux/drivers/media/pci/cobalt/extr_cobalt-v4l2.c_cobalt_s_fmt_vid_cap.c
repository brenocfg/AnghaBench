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
struct v4l2_pix_format {int pixelformat; int /*<<< orphan*/  bytesperline; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_2__ {struct v4l2_pix_format pix; } ;
struct v4l2_format {TYPE_1__ fmt; } ;
struct file {int dummy; } ;
struct cobalt_stream {int pixfmt; int /*<<< orphan*/  bpp; int /*<<< orphan*/  stride; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  q; } ;

/* Variables and functions */
 int /*<<< orphan*/  COBALT_BYTES_PER_PIXEL_RGB24 ; 
 int /*<<< orphan*/  COBALT_BYTES_PER_PIXEL_RGB32 ; 
 int /*<<< orphan*/  COBALT_BYTES_PER_PIXEL_YUYV ; 
 int EBUSY ; 
 int EINVAL ; 
#define  V4L2_PIX_FMT_BGR32 130 
#define  V4L2_PIX_FMT_RGB24 129 
#define  V4L2_PIX_FMT_YUYV 128 
 int /*<<< orphan*/  cobalt_enable_input (struct cobalt_stream*) ; 
 scalar_t__ cobalt_try_fmt_vid_cap (struct file*,void*,struct v4l2_format*) ; 
 scalar_t__ vb2_is_busy (int /*<<< orphan*/ *) ; 
 struct cobalt_stream* video_drvdata (struct file*) ; 

__attribute__((used)) static int cobalt_s_fmt_vid_cap(struct file *file, void *priv_fh,
		struct v4l2_format *f)
{
	struct cobalt_stream *s = video_drvdata(file);
	struct v4l2_pix_format *pix = &f->fmt.pix;

	if (vb2_is_busy(&s->q))
		return -EBUSY;

	if (cobalt_try_fmt_vid_cap(file, priv_fh, f))
		return -EINVAL;

	s->width = pix->width;
	s->height = pix->height;
	s->stride = pix->bytesperline;
	switch (pix->pixelformat) {
	case V4L2_PIX_FMT_YUYV:
		s->bpp = COBALT_BYTES_PER_PIXEL_YUYV;
		break;
	case V4L2_PIX_FMT_RGB24:
		s->bpp = COBALT_BYTES_PER_PIXEL_RGB24;
		break;
	case V4L2_PIX_FMT_BGR32:
		s->bpp = COBALT_BYTES_PER_PIXEL_RGB32;
		break;
	default:
		return -EINVAL;
	}
	s->pixfmt = pix->pixelformat;
	cobalt_enable_input(s);

	return 0;
}
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
struct v4l2_subdev_format {int /*<<< orphan*/  format; int /*<<< orphan*/  which; int /*<<< orphan*/  pad; } ;
struct v4l2_pix_format {int width; int height; int pixelformat; int bytesperline; int sizeimage; int /*<<< orphan*/  field; int /*<<< orphan*/  colorspace; } ;
struct TYPE_2__ {struct v4l2_pix_format pix; } ;
struct v4l2_format {TYPE_1__ fmt; } ;
struct file {int dummy; } ;
struct cobalt_stream {int input; int /*<<< orphan*/  sd; int /*<<< orphan*/  pad_source; } ;

/* Variables and functions */
 int COBALT_BYTES_PER_PIXEL_RGB24 ; 
 int COBALT_BYTES_PER_PIXEL_RGB32 ; 
 int COBALT_BYTES_PER_PIXEL_YUYV ; 
 int /*<<< orphan*/  V4L2_COLORSPACE_SRGB ; 
 int /*<<< orphan*/  V4L2_FIELD_NONE ; 
#define  V4L2_PIX_FMT_BGR32 130 
#define  V4L2_PIX_FMT_RGB24 129 
#define  V4L2_PIX_FMT_YUYV 128 
 int /*<<< orphan*/  V4L2_SUBDEV_FORMAT_ACTIVE ; 
 int /*<<< orphan*/  get_fmt ; 
 void* max (int,int) ; 
 int /*<<< orphan*/  pad ; 
 int /*<<< orphan*/  v4l2_fill_pix_format (struct v4l2_pix_format*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_subdev_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct v4l2_subdev_format*) ; 
 struct cobalt_stream* video_drvdata (struct file*) ; 

__attribute__((used)) static int cobalt_try_fmt_vid_cap(struct file *file, void *priv_fh,
		struct v4l2_format *f)
{
	struct cobalt_stream *s = video_drvdata(file);
	struct v4l2_pix_format *pix = &f->fmt.pix;
	struct v4l2_subdev_format sd_fmt;

	/* Check for min (QCIF) and max (Full HD) size */
	if ((pix->width < 176) || (pix->height < 144)) {
		pix->width = 176;
		pix->height = 144;
	}

	if ((pix->width > 1920) || (pix->height > 1080)) {
		pix->width = 1920;
		pix->height = 1080;
	}

	/* Make width multiple of 4 */
	pix->width &= ~0x3;

	/* Make height multiple of 2 */
	pix->height &= ~0x1;

	if (s->input == 1) {
		/* Generator => fixed format only */
		pix->width = 1920;
		pix->height = 1080;
		pix->colorspace = V4L2_COLORSPACE_SRGB;
	} else {
		sd_fmt.pad = s->pad_source;
		sd_fmt.which = V4L2_SUBDEV_FORMAT_ACTIVE;
		v4l2_subdev_call(s->sd, pad, get_fmt, NULL, &sd_fmt);
		v4l2_fill_pix_format(pix, &sd_fmt.format);
	}

	switch (pix->pixelformat) {
	case V4L2_PIX_FMT_YUYV:
	default:
		pix->bytesperline = max(pix->bytesperline & ~0x3,
				pix->width * COBALT_BYTES_PER_PIXEL_YUYV);
		pix->pixelformat = V4L2_PIX_FMT_YUYV;
		break;
	case V4L2_PIX_FMT_RGB24:
		pix->bytesperline = max(pix->bytesperline & ~0x3,
				pix->width * COBALT_BYTES_PER_PIXEL_RGB24);
		break;
	case V4L2_PIX_FMT_BGR32:
		pix->bytesperline = max(pix->bytesperline & ~0x3,
				pix->width * COBALT_BYTES_PER_PIXEL_RGB32);
		break;
	}

	pix->sizeimage = pix->bytesperline * pix->height;
	pix->field = V4L2_FIELD_NONE;

	return 0;
}
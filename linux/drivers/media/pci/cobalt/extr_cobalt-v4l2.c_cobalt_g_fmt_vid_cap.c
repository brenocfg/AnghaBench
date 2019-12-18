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
struct v4l2_pix_format {int height; int bytesperline; int sizeimage; int /*<<< orphan*/  pixelformat; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  field; int /*<<< orphan*/  width; } ;
struct TYPE_2__ {struct v4l2_pix_format pix; } ;
struct v4l2_format {TYPE_1__ fmt; } ;
struct file {int dummy; } ;
struct cobalt_stream {int height; int stride; int input; int /*<<< orphan*/  pixfmt; int /*<<< orphan*/  sd; int /*<<< orphan*/  pad_source; int /*<<< orphan*/  width; } ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_COLORSPACE_SRGB ; 
 int /*<<< orphan*/  V4L2_FIELD_NONE ; 
 int /*<<< orphan*/  V4L2_SUBDEV_FORMAT_ACTIVE ; 
 int /*<<< orphan*/  get_fmt ; 
 int /*<<< orphan*/  pad ; 
 int /*<<< orphan*/  v4l2_fill_pix_format (struct v4l2_pix_format*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_subdev_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct v4l2_subdev_format*) ; 
 struct cobalt_stream* video_drvdata (struct file*) ; 

__attribute__((used)) static int cobalt_g_fmt_vid_cap(struct file *file, void *priv_fh,
		struct v4l2_format *f)
{
	struct cobalt_stream *s = video_drvdata(file);
	struct v4l2_pix_format *pix = &f->fmt.pix;
	struct v4l2_subdev_format sd_fmt;

	pix->width = s->width;
	pix->height = s->height;
	pix->bytesperline = s->stride;
	pix->field = V4L2_FIELD_NONE;

	if (s->input == 1) {
		pix->colorspace = V4L2_COLORSPACE_SRGB;
	} else {
		sd_fmt.pad = s->pad_source;
		sd_fmt.which = V4L2_SUBDEV_FORMAT_ACTIVE;
		v4l2_subdev_call(s->sd, pad, get_fmt, NULL, &sd_fmt);
		v4l2_fill_pix_format(pix, &sd_fmt.format);
	}

	pix->pixelformat = s->pixfmt;
	pix->sizeimage = pix->bytesperline * pix->height;

	return 0;
}
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
struct v4l2_pix_format {scalar_t__ pixelformat; int sizeimage; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  field; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_2__ {struct v4l2_pix_format pix; } ;
struct v4l2_format {TYPE_1__ fmt; } ;
struct solo_dev {int /*<<< orphan*/  video_hsize; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  V4L2_COLORSPACE_SMPTE170M ; 
 int /*<<< orphan*/  V4L2_FIELD_INTERLACED ; 
 scalar_t__ V4L2_PIX_FMT_UYVY ; 
 int solo_image_size (struct solo_dev*) ; 
 int /*<<< orphan*/  solo_vlines (struct solo_dev*) ; 
 struct solo_dev* video_drvdata (struct file*) ; 

__attribute__((used)) static int solo_try_fmt_cap(struct file *file, void *priv,
			    struct v4l2_format *f)
{
	struct solo_dev *solo_dev = video_drvdata(file);
	struct v4l2_pix_format *pix = &f->fmt.pix;
	int image_size = solo_image_size(solo_dev);

	if (pix->pixelformat != V4L2_PIX_FMT_UYVY)
		return -EINVAL;

	pix->width = solo_dev->video_hsize;
	pix->height = solo_vlines(solo_dev);
	pix->sizeimage = image_size;
	pix->field = V4L2_FIELD_INTERLACED;
	pix->pixelformat = V4L2_PIX_FMT_UYVY;
	pix->colorspace = V4L2_COLORSPACE_SMPTE170M;
	return 0;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct vivid_dev {int dummy; } ;
struct v4l2_fract {int numerator; int denominator; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  TPG_PIXEL_ASPECT_NTSC 129 
#define  TPG_PIXEL_ASPECT_PAL 128 
 int V4L2_BUF_TYPE_VIDEO_OUTPUT ; 
 struct vivid_dev* video_drvdata (struct file*) ; 
 int vivid_get_pixel_aspect (struct vivid_dev*) ; 

int vivid_vid_out_g_pixelaspect(struct file *file, void *priv,
				int type, struct v4l2_fract *f)
{
	struct vivid_dev *dev = video_drvdata(file);

	if (type != V4L2_BUF_TYPE_VIDEO_OUTPUT)
		return -EINVAL;

	switch (vivid_get_pixel_aspect(dev)) {
	case TPG_PIXEL_ASPECT_NTSC:
		f->numerator = 11;
		f->denominator = 10;
		break;
	case TPG_PIXEL_ASPECT_PAL:
		f->numerator = 54;
		f->denominator = 59;
		break;
	default:
		break;
	}
	return 0;
}
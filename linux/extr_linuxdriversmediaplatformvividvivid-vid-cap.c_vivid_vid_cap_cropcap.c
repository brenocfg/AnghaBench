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
struct vivid_dev {int dummy; } ;
struct TYPE_2__ {int numerator; int denominator; } ;
struct v4l2_cropcap {scalar_t__ type; TYPE_1__ pixelaspect; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  TPG_PIXEL_ASPECT_NTSC 130 
#define  TPG_PIXEL_ASPECT_PAL 129 
#define  TPG_PIXEL_ASPECT_SQUARE 128 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 struct vivid_dev* video_drvdata (struct file*) ; 
 int vivid_get_pixel_aspect (struct vivid_dev*) ; 

int vivid_vid_cap_cropcap(struct file *file, void *priv,
			      struct v4l2_cropcap *cap)
{
	struct vivid_dev *dev = video_drvdata(file);

	if (cap->type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		return -EINVAL;

	switch (vivid_get_pixel_aspect(dev)) {
	case TPG_PIXEL_ASPECT_NTSC:
		cap->pixelaspect.numerator = 11;
		cap->pixelaspect.denominator = 10;
		break;
	case TPG_PIXEL_ASPECT_PAL:
		cap->pixelaspect.numerator = 54;
		cap->pixelaspect.denominator = 59;
		break;
	case TPG_PIXEL_ASPECT_SQUARE:
		cap->pixelaspect.numerator = 1;
		cap->pixelaspect.denominator = 1;
		break;
	}
	return 0;
}
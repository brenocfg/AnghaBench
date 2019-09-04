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
struct TYPE_4__ {int numerator; int denominator; } ;
struct v4l2_cropcap {scalar_t__ type; TYPE_2__ pixelaspect; } ;
struct saa7134_dev {TYPE_1__* tvnorm; } ;
struct file {int dummy; } ;
struct TYPE_3__ {int id; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_OVERLAY ; 
 int V4L2_STD_525_60 ; 
 int V4L2_STD_625_50 ; 
 struct saa7134_dev* video_drvdata (struct file*) ; 

__attribute__((used)) static int saa7134_cropcap(struct file *file, void *priv,
					struct v4l2_cropcap *cap)
{
	struct saa7134_dev *dev = video_drvdata(file);

	if (cap->type != V4L2_BUF_TYPE_VIDEO_CAPTURE &&
	    cap->type != V4L2_BUF_TYPE_VIDEO_OVERLAY)
		return -EINVAL;
	cap->pixelaspect.numerator   = 1;
	cap->pixelaspect.denominator = 1;
	if (dev->tvnorm->id & V4L2_STD_525_60) {
		cap->pixelaspect.numerator   = 11;
		cap->pixelaspect.denominator = 10;
	}
	if (dev->tvnorm->id & V4L2_STD_625_50) {
		cap->pixelaspect.numerator   = 54;
		cap->pixelaspect.denominator = 59;
	}
	return 0;
}
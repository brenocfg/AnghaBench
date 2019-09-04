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
struct TYPE_3__ {int width; int /*<<< orphan*/  height; scalar_t__ top; scalar_t__ left; } ;
struct v4l2_cropcap {scalar_t__ type; TYPE_2__ pixelaspect; TYPE_1__ bounds; TYPE_1__ defrect; } ;
struct file {int dummy; } ;
struct cx23885_dev {int tvnorm; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 int V4L2_STD_625_50 ; 
 int /*<<< orphan*/  norm_maxh (int) ; 
 struct cx23885_dev* video_drvdata (struct file*) ; 

__attribute__((used)) static int vidioc_cropcap(struct file *file, void *priv,
			  struct v4l2_cropcap *cc)
{
	struct cx23885_dev *dev = video_drvdata(file);
	bool is_50hz = dev->tvnorm & V4L2_STD_625_50;

	if (cc->type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		return -EINVAL;

	cc->bounds.left = 0;
	cc->bounds.top = 0;
	cc->bounds.width = 720;
	cc->bounds.height = norm_maxh(dev->tvnorm);
	cc->defrect = cc->bounds;
	cc->pixelaspect.numerator = is_50hz ? 54 : 11;
	cc->pixelaspect.denominator = is_50hz ? 59 : 10;

	return 0;
}
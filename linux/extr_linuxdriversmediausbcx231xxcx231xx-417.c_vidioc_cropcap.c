#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int numerator; int denominator; } ;
struct TYPE_7__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; scalar_t__ top; scalar_t__ left; } ;
struct v4l2_cropcap {scalar_t__ type; TYPE_4__ pixelaspect; TYPE_3__ bounds; TYPE_3__ defrect; } ;
struct file {int dummy; } ;
struct cx231xx_fh {struct cx231xx* dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_5__ {int id; } ;
struct cx231xx {TYPE_2__ ts1; TYPE_1__ encodernorm; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 int V4L2_STD_625_50 ; 

__attribute__((used)) static int vidioc_cropcap(struct file *file, void *priv,
			  struct v4l2_cropcap *cc)
{
	struct cx231xx_fh *fh = priv;
	struct cx231xx *dev = fh->dev;
	bool is_50hz = dev->encodernorm.id & V4L2_STD_625_50;

	if (cc->type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		return -EINVAL;

	cc->bounds.left = 0;
	cc->bounds.top = 0;
	cc->bounds.width = dev->ts1.width;
	cc->bounds.height = dev->ts1.height;
	cc->defrect = cc->bounds;
	cc->pixelaspect.numerator = is_50hz ? 54 : 11;
	cc->pixelaspect.denominator = is_50hz ? 59 : 10;

	return 0;
}
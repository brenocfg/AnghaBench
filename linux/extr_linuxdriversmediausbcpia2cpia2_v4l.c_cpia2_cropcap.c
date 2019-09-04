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
struct TYPE_6__ {int numerator; int denominator; } ;
struct TYPE_5__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; scalar_t__ top; scalar_t__ left; } ;
struct TYPE_4__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; scalar_t__ top; scalar_t__ left; } ;
struct v4l2_cropcap {scalar_t__ type; TYPE_3__ pixelaspect; TYPE_2__ defrect; TYPE_1__ bounds; } ;
struct file {int dummy; } ;
struct camera_data {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 struct camera_data* video_drvdata (struct file*) ; 

__attribute__((used)) static int cpia2_cropcap(struct file *file, void *fh, struct v4l2_cropcap *c)
{
	struct camera_data *cam = video_drvdata(file);

	if (c->type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
	       return -EINVAL;

	c->bounds.left = 0;
	c->bounds.top = 0;
	c->bounds.width = cam->width;
	c->bounds.height = cam->height;
	c->defrect.left = 0;
	c->defrect.top = 0;
	c->defrect.width = cam->width;
	c->defrect.height = cam->height;
	c->pixelaspect.numerator = 1;
	c->pixelaspect.denominator = 1;

	return 0;
}
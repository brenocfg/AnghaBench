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
typedef  int v4l2_std_id ;
struct TYPE_2__ {int width; int height; int /*<<< orphan*/  code; } ;
struct v4l2_subdev_format {TYPE_1__ format; int /*<<< orphan*/  which; } ;
struct file {int dummy; } ;
struct cx231xx_fh {int /*<<< orphan*/  vb_vidq; struct cx231xx* dev; } ;
struct cx231xx {int norm; int width; int height; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  MEDIA_BUS_FMT_FIXED ; 
 int V4L2_STD_625_50 ; 
 int /*<<< orphan*/  V4L2_SUBDEV_FORMAT_ACTIVE ; 
 int /*<<< orphan*/  call_all (struct cx231xx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,...) ; 
 int check_dev (struct cx231xx*) ; 
 int /*<<< orphan*/  cx231xx_do_mode_ctrl_overrides (struct cx231xx*) ; 
 int /*<<< orphan*/  pad ; 
 int /*<<< orphan*/  s_std ; 
 int /*<<< orphan*/  set_fmt ; 
 int /*<<< orphan*/  video ; 
 scalar_t__ videobuf_queue_is_busy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vidioc_s_std(struct file *file, void *priv, v4l2_std_id norm)
{
	struct cx231xx_fh *fh = priv;
	struct cx231xx *dev = fh->dev;
	struct v4l2_subdev_format format = {
		.which = V4L2_SUBDEV_FORMAT_ACTIVE,
	};
	int rc;

	rc = check_dev(dev);
	if (rc < 0)
		return rc;

	if (dev->norm == norm)
		return 0;

	if (videobuf_queue_is_busy(&fh->vb_vidq))
		return -EBUSY;

	dev->norm = norm;

	/* Adjusts width/height, if needed */
	dev->width = 720;
	dev->height = (dev->norm & V4L2_STD_625_50) ? 576 : 480;

	call_all(dev, video, s_std, dev->norm);

	/* We need to reset basic properties in the decoder related to
	   resolution (since a standard change effects things like the number
	   of lines in VACT, etc) */
	format.format.code = MEDIA_BUS_FMT_FIXED;
	format.format.width = dev->width;
	format.format.height = dev->height;
	call_all(dev, pad, set_fmt, NULL, &format);

	/* do mode control overrides */
	cx231xx_do_mode_ctrl_overrides(dev);

	return 0;
}
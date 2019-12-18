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
struct vpbe_layer {int /*<<< orphan*/  device_id; TYPE_1__* disp_dev; } ;
struct vpbe_device {int /*<<< orphan*/  v4l2_dev; } ;
struct v4l2_fmtdesc {int index; int /*<<< orphan*/  pixelformat; } ;
struct file {int dummy; } ;
struct TYPE_2__ {struct vpbe_device* vpbe_dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  V4L2_PIX_FMT_NV12 ; 
 int /*<<< orphan*/  V4L2_PIX_FMT_UYVY ; 
 int /*<<< orphan*/  debug ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_err (int /*<<< orphan*/ *,char*) ; 
 struct vpbe_layer* video_drvdata (struct file*) ; 

__attribute__((used)) static int vpbe_display_enum_fmt(struct file *file, void  *priv,
				   struct v4l2_fmtdesc *fmt)
{
	struct vpbe_layer *layer = video_drvdata(file);
	struct vpbe_device *vpbe_dev = layer->disp_dev->vpbe_dev;

	v4l2_dbg(1, debug, &vpbe_dev->v4l2_dev,
				"VIDIOC_ENUM_FMT, layer id = %d\n",
				layer->device_id);
	if (fmt->index > 1) {
		v4l2_err(&vpbe_dev->v4l2_dev, "Invalid format index\n");
		return -EINVAL;
	}

	/* Fill in the information about format */
	if (fmt->index == 0)
		fmt->pixelformat = V4L2_PIX_FMT_UYVY;
	else
		fmt->pixelformat = V4L2_PIX_FMT_NV12;

	return 0;
}
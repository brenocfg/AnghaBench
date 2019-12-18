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
struct vpbe_layer {TYPE_1__* disp_dev; } ;
struct v4l2_fract {int dummy; } ;
struct TYPE_4__ {struct v4l2_fract aspect; } ;
struct vpbe_device {TYPE_2__ current_timings; int /*<<< orphan*/  v4l2_dev; } ;
struct file {int dummy; } ;
struct TYPE_3__ {struct vpbe_device* vpbe_dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int V4L2_BUF_TYPE_VIDEO_OUTPUT ; 
 int /*<<< orphan*/  debug ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 struct vpbe_layer* video_drvdata (struct file*) ; 

__attribute__((used)) static int vpbe_display_g_pixelaspect(struct file *file, void *priv,
				      int type, struct v4l2_fract *f)
{
	struct vpbe_layer *layer = video_drvdata(file);
	struct vpbe_device *vpbe_dev = layer->disp_dev->vpbe_dev;

	v4l2_dbg(1, debug, &vpbe_dev->v4l2_dev, "VIDIOC_CROPCAP ioctl\n");

	if (type != V4L2_BUF_TYPE_VIDEO_OUTPUT)
		return -EINVAL;

	*f = vpbe_dev->current_timings.aspect;
	return 0;
}
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
struct vpbe_layer {int /*<<< orphan*/  buffer_queue; TYPE_2__* disp_dev; } ;
struct TYPE_3__ {int (* s_dv_timings ) (struct vpbe_device*,struct v4l2_dv_timings*) ;} ;
struct vpbe_device {int /*<<< orphan*/  v4l2_dev; TYPE_1__ ops; } ;
struct v4l2_dv_timings {int dummy; } ;
struct file {int dummy; } ;
struct TYPE_4__ {struct vpbe_device* vpbe_dev; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  debug ; 
 int stub1 (struct vpbe_device*,struct v4l2_dv_timings*) ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  v4l2_err (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ vb2_is_busy (int /*<<< orphan*/ *) ; 
 struct vpbe_layer* video_drvdata (struct file*) ; 

__attribute__((used)) static int
vpbe_display_s_dv_timings(struct file *file, void *priv,
				struct v4l2_dv_timings *timings)
{
	struct vpbe_layer *layer = video_drvdata(file);
	struct vpbe_device *vpbe_dev = layer->disp_dev->vpbe_dev;
	int ret;

	v4l2_dbg(1, debug, &vpbe_dev->v4l2_dev, "VIDIOC_S_DV_TIMINGS\n");

	if (vb2_is_busy(&layer->buffer_queue))
		return -EBUSY;

	/* Set the given standard in the encoder */
	if (!vpbe_dev->ops.s_dv_timings)
		return -EINVAL;

	ret = vpbe_dev->ops.s_dv_timings(vpbe_dev, timings);
	if (ret) {
		v4l2_err(&vpbe_dev->v4l2_dev,
			"Failed to set the dv timings info\n");
		return -EINVAL;
	}

	return 0;
}
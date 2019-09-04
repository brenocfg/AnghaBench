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
struct v4l2_device {int dummy; } ;
struct isp_prev_device {int /*<<< orphan*/  video_out; int /*<<< orphan*/  video_in; int /*<<< orphan*/  subdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  omap3isp_preview_unregister_entities (struct isp_prev_device*) ; 
 int omap3isp_video_register (int /*<<< orphan*/ *,struct v4l2_device*) ; 
 int v4l2_device_register_subdev (struct v4l2_device*,int /*<<< orphan*/ *) ; 

int omap3isp_preview_register_entities(struct isp_prev_device *prev,
	struct v4l2_device *vdev)
{
	int ret;

	/* Register the subdev and video nodes. */
	ret = v4l2_device_register_subdev(vdev, &prev->subdev);
	if (ret < 0)
		goto error;

	ret = omap3isp_video_register(&prev->video_in, vdev);
	if (ret < 0)
		goto error;

	ret = omap3isp_video_register(&prev->video_out, vdev);
	if (ret < 0)
		goto error;

	return 0;

error:
	omap3isp_preview_unregister_entities(prev);
	return ret;
}
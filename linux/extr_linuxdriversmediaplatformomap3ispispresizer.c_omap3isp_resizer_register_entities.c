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
struct isp_res_device {int /*<<< orphan*/  video_out; int /*<<< orphan*/  video_in; int /*<<< orphan*/  subdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  omap3isp_resizer_unregister_entities (struct isp_res_device*) ; 
 int omap3isp_video_register (int /*<<< orphan*/ *,struct v4l2_device*) ; 
 int v4l2_device_register_subdev (struct v4l2_device*,int /*<<< orphan*/ *) ; 

int omap3isp_resizer_register_entities(struct isp_res_device *res,
				       struct v4l2_device *vdev)
{
	int ret;

	/* Register the subdev and video nodes. */
	ret = v4l2_device_register_subdev(vdev, &res->subdev);
	if (ret < 0)
		goto error;

	ret = omap3isp_video_register(&res->video_in, vdev);
	if (ret < 0)
		goto error;

	ret = omap3isp_video_register(&res->video_out, vdev);
	if (ret < 0)
		goto error;

	return 0;

error:
	omap3isp_resizer_unregister_entities(res);
	return ret;
}
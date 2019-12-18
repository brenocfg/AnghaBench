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
struct iss_ipipe_device {int /*<<< orphan*/  subdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  omap4iss_ipipe_unregister_entities (struct iss_ipipe_device*) ; 
 int v4l2_device_register_subdev (struct v4l2_device*,int /*<<< orphan*/ *) ; 

int omap4iss_ipipe_register_entities(struct iss_ipipe_device *ipipe,
				     struct v4l2_device *vdev)
{
	int ret;

	/* Register the subdev and video node. */
	ret = v4l2_device_register_subdev(vdev, &ipipe->subdev);
	if (ret < 0)
		goto error;

	return 0;

error:
	omap4iss_ipipe_unregister_entities(ipipe);
	return ret;
}
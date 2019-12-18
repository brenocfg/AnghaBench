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
struct TYPE_2__ {scalar_t__ has_417; } ;
struct cx231xx {int /*<<< orphan*/  radio_ctrl_handler; int /*<<< orphan*/  ctrl_handler; int /*<<< orphan*/  vdev; TYPE_1__ board; int /*<<< orphan*/  dev; int /*<<< orphan*/  vbi_dev; int /*<<< orphan*/  radio_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  cx231xx_417_unregister (struct cx231xx*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  video_device_node_name (int /*<<< orphan*/ *) ; 
 scalar_t__ video_is_registered (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  video_unregister_device (int /*<<< orphan*/ *) ; 

void cx231xx_release_analog_resources(struct cx231xx *dev)
{

	/*FIXME: I2C IR should be disconnected */

	if (video_is_registered(&dev->radio_dev))
		video_unregister_device(&dev->radio_dev);
	if (video_is_registered(&dev->vbi_dev)) {
		dev_info(dev->dev, "V4L2 device %s deregistered\n",
			video_device_node_name(&dev->vbi_dev));
		video_unregister_device(&dev->vbi_dev);
	}
	if (video_is_registered(&dev->vdev)) {
		dev_info(dev->dev, "V4L2 device %s deregistered\n",
			video_device_node_name(&dev->vdev));

		if (dev->board.has_417)
			cx231xx_417_unregister(dev);

		video_unregister_device(&dev->vdev);
	}
	v4l2_ctrl_handler_free(&dev->ctrl_handler);
	v4l2_ctrl_handler_free(&dev->radio_ctrl_handler);
}
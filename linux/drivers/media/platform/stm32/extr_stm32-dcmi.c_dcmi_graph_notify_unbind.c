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
struct v4l2_subdev {int dummy; } ;
struct v4l2_async_subdev {int dummy; } ;
struct v4l2_async_notifier {int dummy; } ;
struct stm32_dcmi {int /*<<< orphan*/  vdev; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct stm32_dcmi* notifier_to_dcmi (struct v4l2_async_notifier*) ; 
 int /*<<< orphan*/  video_device_node_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  video_unregister_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dcmi_graph_notify_unbind(struct v4l2_async_notifier *notifier,
				     struct v4l2_subdev *sd,
				     struct v4l2_async_subdev *asd)
{
	struct stm32_dcmi *dcmi = notifier_to_dcmi(notifier);

	dev_dbg(dcmi->dev, "Removing %s\n", video_device_node_name(dcmi->vdev));

	/* Checks internally if vdev has been init or not */
	video_unregister_device(dcmi->vdev);
}
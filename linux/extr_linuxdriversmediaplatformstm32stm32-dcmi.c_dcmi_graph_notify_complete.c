#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct v4l2_async_notifier {int dummy; } ;
struct TYPE_6__ {TYPE_1__* subdev; } ;
struct stm32_dcmi {TYPE_3__* vdev; int /*<<< orphan*/  dev; int /*<<< orphan*/  sd_bounds; TYPE_2__ entity; } ;
struct TYPE_7__ {int /*<<< orphan*/  ctrl_handler; } ;
struct TYPE_5__ {int /*<<< orphan*/  ctrl_handler; } ;

/* Variables and functions */
 int /*<<< orphan*/  VFL_TYPE_GRABBER ; 
 int dcmi_formats_init (struct stm32_dcmi*) ; 
 int dcmi_framesizes_init (struct stm32_dcmi*) ; 
 int dcmi_get_sensor_bounds (struct stm32_dcmi*,int /*<<< orphan*/ *) ; 
 int dcmi_set_default_fmt (struct stm32_dcmi*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct stm32_dcmi* notifier_to_dcmi (struct v4l2_async_notifier*) ; 
 int /*<<< orphan*/  video_device_node_name (TYPE_3__*) ; 
 int video_register_device (TYPE_3__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int dcmi_graph_notify_complete(struct v4l2_async_notifier *notifier)
{
	struct stm32_dcmi *dcmi = notifier_to_dcmi(notifier);
	int ret;

	dcmi->vdev->ctrl_handler = dcmi->entity.subdev->ctrl_handler;
	ret = dcmi_formats_init(dcmi);
	if (ret) {
		dev_err(dcmi->dev, "No supported mediabus format found\n");
		return ret;
	}

	ret = dcmi_framesizes_init(dcmi);
	if (ret) {
		dev_err(dcmi->dev, "Could not initialize framesizes\n");
		return ret;
	}

	ret = dcmi_get_sensor_bounds(dcmi, &dcmi->sd_bounds);
	if (ret) {
		dev_err(dcmi->dev, "Could not get sensor bounds\n");
		return ret;
	}

	ret = dcmi_set_default_fmt(dcmi);
	if (ret) {
		dev_err(dcmi->dev, "Could not set default format\n");
		return ret;
	}

	ret = video_register_device(dcmi->vdev, VFL_TYPE_GRABBER, -1);
	if (ret) {
		dev_err(dcmi->dev, "Failed to register video device\n");
		return ret;
	}

	dev_dbg(dcmi->dev, "Device registered as %s\n",
		video_device_node_name(dcmi->vdev));
	return 0;
}
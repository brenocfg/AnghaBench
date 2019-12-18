#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct v4l2_async_notifier {int dummy; } ;
struct TYPE_5__ {TYPE_3__* source; } ;
struct stm32_dcmi {int /*<<< orphan*/  dev; int /*<<< orphan*/  sd_bounds; TYPE_2__ entity; TYPE_1__* vdev; } ;
struct TYPE_6__ {int /*<<< orphan*/  ctrl_handler; } ;
struct TYPE_4__ {int /*<<< orphan*/  ctrl_handler; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  dcmi_find_source (struct stm32_dcmi*) ; 
 int dcmi_formats_init (struct stm32_dcmi*) ; 
 int dcmi_framesizes_init (struct stm32_dcmi*) ; 
 int dcmi_get_sensor_bounds (struct stm32_dcmi*,int /*<<< orphan*/ *) ; 
 int dcmi_set_default_fmt (struct stm32_dcmi*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 TYPE_3__* media_entity_to_v4l2_subdev (int /*<<< orphan*/ ) ; 
 struct stm32_dcmi* notifier_to_dcmi (struct v4l2_async_notifier*) ; 

__attribute__((used)) static int dcmi_graph_notify_complete(struct v4l2_async_notifier *notifier)
{
	struct stm32_dcmi *dcmi = notifier_to_dcmi(notifier);
	int ret;

	/*
	 * Now that the graph is complete,
	 * we search for the source subdevice
	 * in order to expose it through V4L2 interface
	 */
	dcmi->entity.source =
		media_entity_to_v4l2_subdev(dcmi_find_source(dcmi));
	if (!dcmi->entity.source) {
		dev_err(dcmi->dev, "Source subdevice not found\n");
		return -ENODEV;
	}

	dcmi->vdev->ctrl_handler = dcmi->entity.source->ctrl_handler;

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

	return 0;
}
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
struct atmel_isi {TYPE_3__* vdev; int /*<<< orphan*/  dev; TYPE_2__ entity; } ;
struct TYPE_7__ {int /*<<< orphan*/  ctrl_handler; } ;
struct TYPE_5__ {int /*<<< orphan*/  ctrl_handler; } ;

/* Variables and functions */
 int /*<<< orphan*/  VFL_TYPE_GRABBER ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  isi_camera_set_bus_param (struct atmel_isi*) ; 
 int isi_formats_init (struct atmel_isi*) ; 
 int isi_set_default_fmt (struct atmel_isi*) ; 
 struct atmel_isi* notifier_to_isi (struct v4l2_async_notifier*) ; 
 int /*<<< orphan*/  video_device_node_name (TYPE_3__*) ; 
 int video_register_device (TYPE_3__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int isi_graph_notify_complete(struct v4l2_async_notifier *notifier)
{
	struct atmel_isi *isi = notifier_to_isi(notifier);
	int ret;

	isi->vdev->ctrl_handler = isi->entity.subdev->ctrl_handler;
	ret = isi_formats_init(isi);
	if (ret) {
		dev_err(isi->dev, "No supported mediabus format found\n");
		return ret;
	}
	isi_camera_set_bus_param(isi);

	ret = isi_set_default_fmt(isi);
	if (ret) {
		dev_err(isi->dev, "Could not set default format\n");
		return ret;
	}

	ret = video_register_device(isi->vdev, VFL_TYPE_GRABBER, -1);
	if (ret) {
		dev_err(isi->dev, "Failed to register video device\n");
		return ret;
	}

	dev_dbg(isi->dev, "Device registered as %s\n",
		video_device_node_name(isi->vdev));
	return 0;
}
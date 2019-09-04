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
struct uvc_device {TYPE_1__* udev; } ;
struct uvc_control_info {int size; int /*<<< orphan*/  selector; int /*<<< orphan*/  entity; int /*<<< orphan*/  mappings; } ;
struct uvc_control {int initialized; int /*<<< orphan*/ * uvc_data; TYPE_2__* entity; struct uvc_control_info info; } ;
struct TYPE_4__ {int /*<<< orphan*/  id; } ;
struct TYPE_3__ {int /*<<< orphan*/  devpath; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int UVC_CTRL_DATA_LAST ; 
 int /*<<< orphan*/  UVC_TRACE_CONTROL ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uvc_ctrl_get_flags (struct uvc_device*,struct uvc_control*,struct uvc_control_info*) ; 
 int /*<<< orphan*/  uvc_trace (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int uvc_ctrl_add_info(struct uvc_device *dev, struct uvc_control *ctrl,
	const struct uvc_control_info *info)
{
	int ret = 0;

	ctrl->info = *info;
	INIT_LIST_HEAD(&ctrl->info.mappings);

	/* Allocate an array to save control values (cur, def, max, etc.) */
	ctrl->uvc_data = kzalloc(ctrl->info.size * UVC_CTRL_DATA_LAST + 1,
				 GFP_KERNEL);
	if (ctrl->uvc_data == NULL) {
		ret = -ENOMEM;
		goto done;
	}

	/*
	 * Retrieve control flags from the device. Ignore errors and work with
	 * default flag values from the uvc_ctrl array when the device doesn't
	 * properly implement GET_INFO on standard controls.
	 */
	uvc_ctrl_get_flags(dev, ctrl, &ctrl->info);

	ctrl->initialized = 1;

	uvc_trace(UVC_TRACE_CONTROL, "Added control %pUl/%u to device %s "
		"entity %u\n", ctrl->info.entity, ctrl->info.selector,
		dev->udev->devpath, ctrl->entity->id);

done:
	if (ret < 0)
		kfree(ctrl->uvc_data);
	return ret;
}
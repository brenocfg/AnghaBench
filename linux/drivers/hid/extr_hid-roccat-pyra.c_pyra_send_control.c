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
struct usb_device {int dummy; } ;
struct roccat_common2_control {int value; int request; int /*<<< orphan*/  command; } ;
typedef  enum pyra_control_requests { ____Placeholder_pyra_control_requests } pyra_control_requests ;

/* Variables and functions */
 int EINVAL ; 
 int PYRA_CONTROL_REQUEST_PROFILE_BUTTONS ; 
 int PYRA_CONTROL_REQUEST_PROFILE_SETTINGS ; 
 int /*<<< orphan*/  ROCCAT_COMMON_COMMAND_CONTROL ; 
 int roccat_common2_send (struct usb_device*,int /*<<< orphan*/ ,struct roccat_common2_control*,int) ; 

__attribute__((used)) static int pyra_send_control(struct usb_device *usb_dev, int value,
		enum pyra_control_requests request)
{
	struct roccat_common2_control control;

	if ((request == PYRA_CONTROL_REQUEST_PROFILE_SETTINGS ||
			request == PYRA_CONTROL_REQUEST_PROFILE_BUTTONS) &&
			(value < 0 || value > 4))
		return -EINVAL;

	control.command = ROCCAT_COMMON_COMMAND_CONTROL;
	control.value = value;
	control.request = request;

	return roccat_common2_send(usb_dev, ROCCAT_COMMON_COMMAND_CONTROL,
			&control, sizeof(struct roccat_common2_control));
}
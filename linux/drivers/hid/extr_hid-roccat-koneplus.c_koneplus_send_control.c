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
typedef  int uint ;
struct usb_device {int dummy; } ;
struct roccat_common2_control {int value; int request; int /*<<< orphan*/  command; } ;
typedef  enum koneplus_control_requests { ____Placeholder_koneplus_control_requests } koneplus_control_requests ;

/* Variables and functions */
 int EINVAL ; 
 int KONEPLUS_CONTROL_REQUEST_PROFILE_BUTTONS ; 
 int KONEPLUS_CONTROL_REQUEST_PROFILE_SETTINGS ; 
 int /*<<< orphan*/  ROCCAT_COMMON_COMMAND_CONTROL ; 
 int roccat_common2_send_with_status (struct usb_device*,int /*<<< orphan*/ ,struct roccat_common2_control*,int) ; 

__attribute__((used)) static int koneplus_send_control(struct usb_device *usb_dev, uint value,
		enum koneplus_control_requests request)
{
	struct roccat_common2_control control;

	if ((request == KONEPLUS_CONTROL_REQUEST_PROFILE_SETTINGS ||
			request == KONEPLUS_CONTROL_REQUEST_PROFILE_BUTTONS) &&
			value > 4)
		return -EINVAL;

	control.command = ROCCAT_COMMON_COMMAND_CONTROL;
	control.value = value;
	control.request = request;

	return roccat_common2_send_with_status(usb_dev,
			ROCCAT_COMMON_COMMAND_CONTROL,
			&control, sizeof(struct roccat_common2_control));
}
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
struct pyra_profile_settings {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PYRA_COMMAND_PROFILE_SETTINGS ; 
 int /*<<< orphan*/  PYRA_CONTROL_REQUEST_PROFILE_SETTINGS ; 
 int /*<<< orphan*/  PYRA_SIZE_PROFILE_SETTINGS ; 
 int pyra_send_control (struct usb_device*,int,int /*<<< orphan*/ ) ; 
 int roccat_common2_receive (struct usb_device*,int /*<<< orphan*/ ,struct pyra_profile_settings*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pyra_get_profile_settings(struct usb_device *usb_dev,
		struct pyra_profile_settings *buf, int number)
{
	int retval;
	retval = pyra_send_control(usb_dev, number,
			PYRA_CONTROL_REQUEST_PROFILE_SETTINGS);
	if (retval)
		return retval;
	return roccat_common2_receive(usb_dev, PYRA_COMMAND_PROFILE_SETTINGS,
			buf, PYRA_SIZE_PROFILE_SETTINGS);
}
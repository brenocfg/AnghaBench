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
typedef  int /*<<< orphan*/  uint ;
struct usb_device {int dummy; } ;
struct kovaplus_profile_settings {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KOVAPLUS_COMMAND_PROFILE_SETTINGS ; 
 int /*<<< orphan*/  KOVAPLUS_CONTROL_REQUEST_PROFILE_SETTINGS ; 
 int /*<<< orphan*/  KOVAPLUS_SIZE_PROFILE_SETTINGS ; 
 int kovaplus_select_profile (struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int roccat_common2_receive (struct usb_device*,int /*<<< orphan*/ ,struct kovaplus_profile_settings*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int kovaplus_get_profile_settings(struct usb_device *usb_dev,
		struct kovaplus_profile_settings *buf, uint number)
{
	int retval;

	retval = kovaplus_select_profile(usb_dev, number,
			KOVAPLUS_CONTROL_REQUEST_PROFILE_SETTINGS);
	if (retval)
		return retval;

	return roccat_common2_receive(usb_dev, KOVAPLUS_COMMAND_PROFILE_SETTINGS,
			buf, KOVAPLUS_SIZE_PROFILE_SETTINGS);
}
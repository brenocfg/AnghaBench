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
struct pyra_settings {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PYRA_COMMAND_SETTINGS ; 
 int /*<<< orphan*/  PYRA_SIZE_SETTINGS ; 
 int roccat_common2_send_with_status (struct usb_device*,int /*<<< orphan*/ ,struct pyra_settings const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pyra_set_settings(struct usb_device *usb_dev,
		struct pyra_settings const *settings)
{
	return roccat_common2_send_with_status(usb_dev,
			PYRA_COMMAND_SETTINGS, settings,
			PYRA_SIZE_SETTINGS);
}
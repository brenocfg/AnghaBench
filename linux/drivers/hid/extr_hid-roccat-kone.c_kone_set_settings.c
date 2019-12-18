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
struct kone_settings {int dummy; } ;

/* Variables and functions */
 int kone_check_write (struct usb_device*) ; 
 int /*<<< orphan*/  kone_command_settings ; 
 int kone_send (struct usb_device*,int /*<<< orphan*/ ,struct kone_settings const*,int) ; 

__attribute__((used)) static int kone_set_settings(struct usb_device *usb_dev,
		struct kone_settings const *settings)
{
	int retval;

	retval = kone_send(usb_dev, kone_command_settings,
			settings, sizeof(struct kone_settings));
	if (retval)
		return retval;
	return kone_check_write(usb_dev);
}
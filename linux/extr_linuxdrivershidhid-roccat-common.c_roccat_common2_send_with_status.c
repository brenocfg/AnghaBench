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

/* Variables and functions */
 int /*<<< orphan*/  msleep (int) ; 
 int roccat_common2_receive_control_status (struct usb_device*) ; 
 int roccat_common2_send (struct usb_device*,int /*<<< orphan*/ ,void const*,int /*<<< orphan*/ ) ; 

int roccat_common2_send_with_status(struct usb_device *usb_dev,
		uint command, void const *buf, uint size)
{
	int retval;

	retval = roccat_common2_send(usb_dev, command, buf, size);
	if (retval)
		return retval;

	msleep(100);

	return roccat_common2_receive_control_status(usb_dev);
}
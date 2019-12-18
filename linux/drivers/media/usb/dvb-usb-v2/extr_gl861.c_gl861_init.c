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
struct dvb_usb_device {int /*<<< orphan*/  udev; } ;

/* Variables and functions */
 int usb_set_interface (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gl861_init(struct dvb_usb_device *d)
{
	/*
	 * There is 2 interfaces. Interface 0 is for TV and interface 1 is
	 * for HID remote controller. Interface 0 has 2 alternate settings.
	 * For some reason we need to set interface explicitly, defaulted
	 * as alternate setting 1?
	 */
	return usb_set_interface(d->udev, 0, 0);
}
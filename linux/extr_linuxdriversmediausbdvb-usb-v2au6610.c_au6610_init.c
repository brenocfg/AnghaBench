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
 int usb_set_interface (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int au6610_init(struct dvb_usb_device *d)
{
	/* TODO: this functionality belongs likely to the streaming control */
	/* bInterfaceNumber 0, bAlternateSetting 5 */
	return usb_set_interface(d->udev, 0, 5);
}
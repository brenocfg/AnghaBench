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
typedef  int /*<<< orphan*/  u8 ;
struct usb_serial {TYPE_1__* interface; } ;
struct TYPE_4__ {int /*<<< orphan*/  bInterfaceNumber; } ;
struct usb_host_interface {TYPE_2__ desc; } ;
struct TYPE_3__ {struct usb_host_interface* cur_altsetting; } ;

/* Variables and functions */

__attribute__((used)) static u8 cp210x_interface_num(struct usb_serial *serial)
{
	struct usb_host_interface *cur_altsetting;

	cur_altsetting = serial->interface->cur_altsetting;

	return cur_altsetting->desc.bInterfaceNumber;
}
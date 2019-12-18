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
struct usb_serial {int num_ports; int /*<<< orphan*/ * port; } ;

/* Variables and functions */
 int /*<<< orphan*/  usb_serial_port_unpoison_urbs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void usb_serial_unpoison_port_urbs(struct usb_serial *serial)
{
	int i;

	for (i = 0; i < serial->num_ports; ++i)
		usb_serial_port_unpoison_urbs(serial->port[i]);
}
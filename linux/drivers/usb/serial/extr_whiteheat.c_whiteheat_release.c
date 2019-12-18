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
struct usb_serial_port {int dummy; } ;
struct usb_serial {struct usb_serial_port** port; } ;

/* Variables and functions */
 size_t COMMAND_PORT ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_get_serial_port_data (struct usb_serial_port*) ; 

__attribute__((used)) static void whiteheat_release(struct usb_serial *serial)
{
	struct usb_serial_port *command_port;

	/* free up our private data for our command port */
	command_port = serial->port[COMMAND_PORT];
	kfree(usb_get_serial_port_data(command_port));
}
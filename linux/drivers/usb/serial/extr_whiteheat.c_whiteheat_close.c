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
struct usb_serial_port {int /*<<< orphan*/  serial; } ;

/* Variables and functions */
 int /*<<< orphan*/  firm_close (struct usb_serial_port*) ; 
 int /*<<< orphan*/  firm_report_tx_done (struct usb_serial_port*) ; 
 int /*<<< orphan*/  stop_command_port (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_serial_generic_close (struct usb_serial_port*) ; 

__attribute__((used)) static void whiteheat_close(struct usb_serial_port *port)
{
	firm_report_tx_done(port);
	firm_close(port);

	usb_serial_generic_close(port);

	stop_command_port(port->serial);
}
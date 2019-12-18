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
struct usb_serial_port {int /*<<< orphan*/  interrupt_in_urb; } ;

/* Variables and functions */
 int /*<<< orphan*/  UNI_CMD_CLOSE ; 
 int /*<<< orphan*/  metrousb_send_unidirectional_cmd (int /*<<< orphan*/ ,struct usb_serial_port*) ; 
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void metrousb_cleanup(struct usb_serial_port *port)
{
	usb_kill_urb(port->interrupt_in_urb);

	metrousb_send_unidirectional_cmd(UNI_CMD_CLOSE, port);
}
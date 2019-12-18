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
struct usb_serial_port {int /*<<< orphan*/  interrupt_in_urb; struct usb_serial* serial; } ;
struct usb_serial {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  UART_FCR ; 
 int /*<<< orphan*/  UART_IER ; 
 int /*<<< orphan*/  ark3116_write_reg (struct usb_serial*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_serial_generic_close (struct usb_serial_port*) ; 

__attribute__((used)) static void ark3116_close(struct usb_serial_port *port)
{
	struct usb_serial *serial = port->serial;

	/* disable DMA */
	ark3116_write_reg(serial, UART_FCR, 0);

	/* deactivate interrupts */
	ark3116_write_reg(serial, UART_IER, 0);

	usb_serial_generic_close(port);

	usb_kill_urb(port->interrupt_in_urb);
}
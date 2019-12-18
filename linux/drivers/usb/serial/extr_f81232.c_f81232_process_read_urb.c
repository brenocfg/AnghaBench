#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_5__ {scalar_t__ console; } ;
struct TYPE_4__ {int /*<<< orphan*/  overrun; int /*<<< orphan*/  frame; int /*<<< orphan*/  parity; int /*<<< orphan*/  brk; } ;
struct usb_serial_port {TYPE_2__ port; scalar_t__ sysrq; TYPE_1__ icount; } ;
struct urb {unsigned char* transfer_buffer; int actual_length; struct usb_serial_port* context; } ;
struct f81232_private {int /*<<< orphan*/  lsr_work; } ;

/* Variables and functions */
 char TTY_BREAK ; 
 char TTY_FRAME ; 
 char TTY_NORMAL ; 
 char TTY_OVERRUN ; 
 char TTY_PARITY ; 
 int UART_LSR_BI ; 
 int UART_LSR_BRK_ERROR_BITS ; 
 int UART_LSR_FE ; 
 int UART_LSR_OE ; 
 int UART_LSR_PE ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_flip_buffer_push (TYPE_2__*) ; 
 int /*<<< orphan*/  tty_insert_flip_char (TYPE_2__*,unsigned char,char) ; 
 struct f81232_private* usb_get_serial_port_data (struct usb_serial_port*) ; 
 int /*<<< orphan*/  usb_serial_handle_break (struct usb_serial_port*) ; 
 scalar_t__ usb_serial_handle_sysrq_char (struct usb_serial_port*,unsigned char) ; 

__attribute__((used)) static void f81232_process_read_urb(struct urb *urb)
{
	struct usb_serial_port *port = urb->context;
	struct f81232_private *priv = usb_get_serial_port_data(port);
	unsigned char *data = urb->transfer_buffer;
	char tty_flag;
	unsigned int i;
	u8 lsr;

	/*
	 * When opening the port we get a 1-byte packet with the current LSR,
	 * which we discard.
	 */
	if ((urb->actual_length < 2) || (urb->actual_length % 2))
		return;

	/* bulk-in data: [LSR(1Byte)+DATA(1Byte)][LSR(1Byte)+DATA(1Byte)]... */

	for (i = 0; i < urb->actual_length; i += 2) {
		tty_flag = TTY_NORMAL;
		lsr = data[i];

		if (lsr & UART_LSR_BRK_ERROR_BITS) {
			if (lsr & UART_LSR_BI) {
				tty_flag = TTY_BREAK;
				port->icount.brk++;
				usb_serial_handle_break(port);
			} else if (lsr & UART_LSR_PE) {
				tty_flag = TTY_PARITY;
				port->icount.parity++;
			} else if (lsr & UART_LSR_FE) {
				tty_flag = TTY_FRAME;
				port->icount.frame++;
			}

			if (lsr & UART_LSR_OE) {
				port->icount.overrun++;
				schedule_work(&priv->lsr_work);
				tty_insert_flip_char(&port->port, 0,
						TTY_OVERRUN);
			}
		}

		if (port->port.console && port->sysrq) {
			if (usb_serial_handle_sysrq_char(port, data[i + 1]))
				continue;
		}

		tty_insert_flip_char(&port->port, data[i + 1], tty_flag);
	}

	tty_flip_buffer_push(&port->port);
}
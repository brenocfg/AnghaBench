#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tcflag_t ;
struct usb_serial_port {int dummy; } ;
struct TYPE_2__ {scalar_t__ c_cflag; } ;
struct tty_struct {TYPE_1__ termios; struct usb_serial_port* driver_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  cp210x_get_termios_port (struct usb_serial_port*,scalar_t__*,unsigned int*) ; 
 int /*<<< orphan*/  tty_encode_baud_rate (struct tty_struct*,unsigned int,unsigned int) ; 

__attribute__((used)) static void cp210x_get_termios(struct tty_struct *tty,
	struct usb_serial_port *port)
{
	unsigned int baud;

	if (tty) {
		cp210x_get_termios_port(tty->driver_data,
			&tty->termios.c_cflag, &baud);
		tty_encode_baud_rate(tty, baud, baud);
	} else {
		tcflag_t cflag;
		cflag = 0;
		cp210x_get_termios_port(port, &cflag, &baud);
	}
}
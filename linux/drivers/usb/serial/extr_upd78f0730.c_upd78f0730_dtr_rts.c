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
struct TYPE_2__ {struct tty_struct* tty; } ;
struct usb_serial_port {TYPE_1__ port; } ;
struct tty_struct {int dummy; } ;

/* Variables and functions */
 unsigned int TIOCM_DTR ; 
 unsigned int TIOCM_RTS ; 
 int /*<<< orphan*/  upd78f0730_tiocmset (struct tty_struct*,unsigned int,unsigned int) ; 

__attribute__((used)) static void upd78f0730_dtr_rts(struct usb_serial_port *port, int on)
{
	struct tty_struct *tty = port->port.tty;
	unsigned int set = 0;
	unsigned int clear = 0;

	if (on)
		set = TIOCM_DTR | TIOCM_RTS;
	else
		clear = TIOCM_DTR | TIOCM_RTS;

	upd78f0730_tiocmset(tty, set, clear);
}
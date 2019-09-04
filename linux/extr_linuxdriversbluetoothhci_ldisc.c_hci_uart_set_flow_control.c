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
struct ktermios {int /*<<< orphan*/  c_cflag; } ;
struct tty_struct {struct ktermios termios; TYPE_2__* driver; } ;
struct hci_uart {scalar_t__ serdev; struct tty_struct* tty; } ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct TYPE_3__ {int (* tiocmget ) (struct tty_struct*) ;int (* tiocmset ) (struct tty_struct*,unsigned int,unsigned int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,...) ; 
 int /*<<< orphan*/  CRTSCTS ; 
 unsigned int TIOCM_DTR ; 
 unsigned int TIOCM_LOOP ; 
 unsigned int TIOCM_OUT1 ; 
 unsigned int TIOCM_OUT2 ; 
 unsigned int TIOCM_RTS ; 
 int /*<<< orphan*/  serdev_device_set_flow_control (scalar_t__,int) ; 
 int /*<<< orphan*/  serdev_device_set_rts (scalar_t__,int) ; 
 int stub1 (struct tty_struct*) ; 
 int stub2 (struct tty_struct*,unsigned int,unsigned int) ; 
 int stub3 (struct tty_struct*) ; 
 int stub4 (struct tty_struct*,unsigned int,unsigned int) ; 
 int tty_set_termios (struct tty_struct*,struct ktermios*) ; 

void hci_uart_set_flow_control(struct hci_uart *hu, bool enable)
{
	struct tty_struct *tty = hu->tty;
	struct ktermios ktermios;
	int status;
	unsigned int set = 0;
	unsigned int clear = 0;

	if (hu->serdev) {
		serdev_device_set_flow_control(hu->serdev, !enable);
		serdev_device_set_rts(hu->serdev, !enable);
		return;
	}

	if (enable) {
		/* Disable hardware flow control */
		ktermios = tty->termios;
		ktermios.c_cflag &= ~CRTSCTS;
		status = tty_set_termios(tty, &ktermios);
		BT_DBG("Disabling hardware flow control: %s",
		       status ? "failed" : "success");

		/* Clear RTS to prevent the device from sending */
		/* Most UARTs need OUT2 to enable interrupts */
		status = tty->driver->ops->tiocmget(tty);
		BT_DBG("Current tiocm 0x%x", status);

		set &= ~(TIOCM_OUT2 | TIOCM_RTS);
		clear = ~set;
		set &= TIOCM_DTR | TIOCM_RTS | TIOCM_OUT1 |
		       TIOCM_OUT2 | TIOCM_LOOP;
		clear &= TIOCM_DTR | TIOCM_RTS | TIOCM_OUT1 |
			 TIOCM_OUT2 | TIOCM_LOOP;
		status = tty->driver->ops->tiocmset(tty, set, clear);
		BT_DBG("Clearing RTS: %s", status ? "failed" : "success");
	} else {
		/* Set RTS to allow the device to send again */
		status = tty->driver->ops->tiocmget(tty);
		BT_DBG("Current tiocm 0x%x", status);

		set |= (TIOCM_OUT2 | TIOCM_RTS);
		clear = ~set;
		set &= TIOCM_DTR | TIOCM_RTS | TIOCM_OUT1 |
		       TIOCM_OUT2 | TIOCM_LOOP;
		clear &= TIOCM_DTR | TIOCM_RTS | TIOCM_OUT1 |
			 TIOCM_OUT2 | TIOCM_LOOP;
		status = tty->driver->ops->tiocmset(tty, set, clear);
		BT_DBG("Setting RTS: %s", status ? "failed" : "success");

		/* Re-enable hardware flow control */
		ktermios = tty->termios;
		ktermios.c_cflag |= CRTSCTS;
		status = tty_set_termios(tty, &ktermios);
		BT_DBG("Enabling hardware flow control: %s",
		       status ? "failed" : "success");
	}
}
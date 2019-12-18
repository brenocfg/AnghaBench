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
struct TYPE_2__ {unsigned int c_cflag; } ;
struct tty_struct {int hw_stopped; TYPE_1__ termios; struct sdio_uart_port* driver_data; } ;
struct sdio_uart_port {int dummy; } ;
struct ktermios {unsigned int c_cflag; } ;

/* Variables and functions */
 unsigned int CBAUD ; 
 unsigned int CRTSCTS ; 
 int TIOCM_CTS ; 
 unsigned int TIOCM_DTR ; 
 unsigned int TIOCM_RTS ; 
 int /*<<< orphan*/  sdio_uart_change_speed (struct sdio_uart_port*,TYPE_1__*,struct ktermios*) ; 
 scalar_t__ sdio_uart_claim_func (struct sdio_uart_port*) ; 
 int /*<<< orphan*/  sdio_uart_clear_mctrl (struct sdio_uart_port*,unsigned int) ; 
 int sdio_uart_get_mctrl (struct sdio_uart_port*) ; 
 int /*<<< orphan*/  sdio_uart_release_func (struct sdio_uart_port*) ; 
 int /*<<< orphan*/  sdio_uart_set_mctrl (struct sdio_uart_port*,unsigned int) ; 
 int /*<<< orphan*/  sdio_uart_start_tx (struct sdio_uart_port*) ; 
 int /*<<< orphan*/  sdio_uart_stop_tx (struct sdio_uart_port*) ; 
 int /*<<< orphan*/  tty_throttled (struct tty_struct*) ; 

__attribute__((used)) static void sdio_uart_set_termios(struct tty_struct *tty,
						struct ktermios *old_termios)
{
	struct sdio_uart_port *port = tty->driver_data;
	unsigned int cflag = tty->termios.c_cflag;

	if (sdio_uart_claim_func(port) != 0)
		return;

	sdio_uart_change_speed(port, &tty->termios, old_termios);

	/* Handle transition to B0 status */
	if ((old_termios->c_cflag & CBAUD) && !(cflag & CBAUD))
		sdio_uart_clear_mctrl(port, TIOCM_RTS | TIOCM_DTR);

	/* Handle transition away from B0 status */
	if (!(old_termios->c_cflag & CBAUD) && (cflag & CBAUD)) {
		unsigned int mask = TIOCM_DTR;
		if (!(cflag & CRTSCTS) || !tty_throttled(tty))
			mask |= TIOCM_RTS;
		sdio_uart_set_mctrl(port, mask);
	}

	/* Handle turning off CRTSCTS */
	if ((old_termios->c_cflag & CRTSCTS) && !(cflag & CRTSCTS)) {
		tty->hw_stopped = 0;
		sdio_uart_start_tx(port);
	}

	/* Handle turning on CRTSCTS */
	if (!(old_termios->c_cflag & CRTSCTS) && (cflag & CRTSCTS)) {
		if (!(sdio_uart_get_mctrl(port) & TIOCM_CTS)) {
			tty->hw_stopped = 1;
			sdio_uart_stop_tx(port);
		}
	}

	sdio_uart_release_func(port);
}
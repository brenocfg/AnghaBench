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
struct uart_state {int dummy; } ;
struct uart_port {scalar_t__ type; int hw_stopped; int /*<<< orphan*/  lock; TYPE_1__* ops; int /*<<< orphan*/  status; } ;
struct ktermios {int c_cflag; } ;
struct tty_struct {struct ktermios termios; } ;
struct TYPE_2__ {int (* get_mctrl ) (struct uart_port*) ;int /*<<< orphan*/  (* stop_tx ) (struct uart_port*) ;int /*<<< orphan*/  (* set_termios ) (struct uart_port*,struct ktermios*,struct ktermios*) ;} ;

/* Variables and functions */
 int CLOCAL ; 
 int CRTSCTS ; 
 scalar_t__ PORT_UNKNOWN ; 
 int TIOCM_CTS ; 
 int /*<<< orphan*/  UPSTAT_CTS_ENABLE ; 
 int /*<<< orphan*/  UPSTAT_DCD_ENABLE ; 
 int /*<<< orphan*/  __uart_start (struct tty_struct*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct uart_port*,struct ktermios*,struct ktermios*) ; 
 int stub2 (struct uart_port*) ; 
 int /*<<< orphan*/  stub3 (struct uart_port*) ; 
 struct uart_port* uart_port_check (struct uart_state*) ; 
 scalar_t__ uart_softcts_mode (struct uart_port*) ; 

__attribute__((used)) static void uart_change_speed(struct tty_struct *tty, struct uart_state *state,
					struct ktermios *old_termios)
{
	struct uart_port *uport = uart_port_check(state);
	struct ktermios *termios;
	int hw_stopped;

	/*
	 * If we have no tty, termios, or the port does not exist,
	 * then we can't set the parameters for this port.
	 */
	if (!tty || uport->type == PORT_UNKNOWN)
		return;

	termios = &tty->termios;
	uport->ops->set_termios(uport, termios, old_termios);

	/*
	 * Set modem status enables based on termios cflag
	 */
	spin_lock_irq(&uport->lock);
	if (termios->c_cflag & CRTSCTS)
		uport->status |= UPSTAT_CTS_ENABLE;
	else
		uport->status &= ~UPSTAT_CTS_ENABLE;

	if (termios->c_cflag & CLOCAL)
		uport->status &= ~UPSTAT_DCD_ENABLE;
	else
		uport->status |= UPSTAT_DCD_ENABLE;

	/* reset sw-assisted CTS flow control based on (possibly) new mode */
	hw_stopped = uport->hw_stopped;
	uport->hw_stopped = uart_softcts_mode(uport) &&
				!(uport->ops->get_mctrl(uport) & TIOCM_CTS);
	if (uport->hw_stopped) {
		if (!hw_stopped)
			uport->ops->stop_tx(uport);
	} else {
		if (hw_stopped)
			__uart_start(tty);
	}
	spin_unlock_irq(&uport->lock);
}
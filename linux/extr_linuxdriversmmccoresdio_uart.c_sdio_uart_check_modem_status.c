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
struct tty_struct {int hw_stopped; } ;
struct TYPE_5__ {int /*<<< orphan*/  open_wait; } ;
struct TYPE_4__ {int /*<<< orphan*/  cts; int /*<<< orphan*/  dcd; int /*<<< orphan*/  dsr; int /*<<< orphan*/  rng; } ;
struct sdio_uart_port {TYPE_2__ port; TYPE_1__ icount; } ;

/* Variables and functions */
 scalar_t__ C_CRTSCTS (struct tty_struct*) ; 
 int /*<<< orphan*/  UART_MSR ; 
 int UART_MSR_ANY_DELTA ; 
 int UART_MSR_CTS ; 
 int UART_MSR_DCD ; 
 int UART_MSR_DCTS ; 
 int UART_MSR_DDCD ; 
 int UART_MSR_DDSR ; 
 int UART_MSR_TERI ; 
 int sdio_in (struct sdio_uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdio_uart_start_tx (struct sdio_uart_port*) ; 
 int /*<<< orphan*/  sdio_uart_stop_tx (struct sdio_uart_port*) ; 
 int /*<<< orphan*/  tty_kref_put (struct tty_struct*) ; 
 struct tty_struct* tty_port_tty_get (TYPE_2__*) ; 
 int /*<<< orphan*/  tty_port_tty_hangup (TYPE_2__*,int) ; 
 int /*<<< orphan*/  tty_wakeup (struct tty_struct*) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sdio_uart_check_modem_status(struct sdio_uart_port *port)
{
	int status;
	struct tty_struct *tty;

	status = sdio_in(port, UART_MSR);

	if ((status & UART_MSR_ANY_DELTA) == 0)
		return;

	if (status & UART_MSR_TERI)
		port->icount.rng++;
	if (status & UART_MSR_DDSR)
		port->icount.dsr++;
	if (status & UART_MSR_DDCD) {
		port->icount.dcd++;
		/* DCD raise - wake for open */
		if (status & UART_MSR_DCD)
			wake_up_interruptible(&port->port.open_wait);
		else {
			/* DCD drop - hang up if tty attached */
			tty_port_tty_hangup(&port->port, false);
		}
	}
	if (status & UART_MSR_DCTS) {
		port->icount.cts++;
		tty = tty_port_tty_get(&port->port);
		if (tty && C_CRTSCTS(tty)) {
			int cts = (status & UART_MSR_CTS);
			if (tty->hw_stopped) {
				if (cts) {
					tty->hw_stopped = 0;
					sdio_uart_start_tx(port);
					tty_wakeup(tty);
				}
			} else {
				if (!cts) {
					tty->hw_stopped = 1;
					sdio_uart_stop_tx(port);
				}
			}
		}
		tty_kref_put(tty);
	}
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {unsigned char* buf; } ;
struct uart_state {TYPE_4__ xmit; } ;
struct uart_port {scalar_t__ type; TYPE_3__* cons; TYPE_1__* ops; } ;
struct TYPE_6__ {scalar_t__ c_cflag; } ;
struct tty_struct {TYPE_2__ termios; } ;
struct TYPE_7__ {scalar_t__ cflag; } ;
struct TYPE_5__ {int (* startup ) (struct uart_port*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 scalar_t__ C_BAUD (struct tty_struct*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ PORT_UNKNOWN ; 
 int /*<<< orphan*/  UART_PM_STATE_ON ; 
 scalar_t__ capable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 unsigned long get_zeroed_page (int /*<<< orphan*/ ) ; 
 int stub1 (struct uart_port*) ; 
 int /*<<< orphan*/  uart_change_pm (struct uart_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_change_speed (struct tty_struct*,struct uart_state*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uart_circ_clear (TYPE_4__*) ; 
 scalar_t__ uart_console (struct uart_port*) ; 
 struct uart_port* uart_port_check (struct uart_state*) ; 
 int /*<<< orphan*/  uart_port_dtr_rts (struct uart_port*,int) ; 
 int /*<<< orphan*/  uart_port_lock (struct uart_state*,unsigned long) ; 
 int /*<<< orphan*/  uart_port_unlock (struct uart_port*,unsigned long) ; 

__attribute__((used)) static int uart_port_startup(struct tty_struct *tty, struct uart_state *state,
		int init_hw)
{
	struct uart_port *uport = uart_port_check(state);
	unsigned long page;
	unsigned long flags = 0;
	int retval = 0;

	if (uport->type == PORT_UNKNOWN)
		return 1;

	/*
	 * Make sure the device is in D0 state.
	 */
	uart_change_pm(state, UART_PM_STATE_ON);

	/*
	 * Initialise and allocate the transmit and temporary
	 * buffer.
	 */
	page = get_zeroed_page(GFP_KERNEL);
	if (!page)
		return -ENOMEM;

	uart_port_lock(state, flags);
	if (!state->xmit.buf) {
		state->xmit.buf = (unsigned char *) page;
		uart_circ_clear(&state->xmit);
		uart_port_unlock(uport, flags);
	} else {
		uart_port_unlock(uport, flags);
		/*
		 * Do not free() the page under the port lock, see
		 * uart_shutdown().
		 */
		free_page(page);
	}

	retval = uport->ops->startup(uport);
	if (retval == 0) {
		if (uart_console(uport) && uport->cons->cflag) {
			tty->termios.c_cflag = uport->cons->cflag;
			uport->cons->cflag = 0;
		}
		/*
		 * Initialise the hardware port settings.
		 */
		uart_change_speed(tty, state, NULL);

		/*
		 * Setup the RTS and DTR signals once the
		 * port is open and ready to respond.
		 */
		if (init_hw && C_BAUD(tty))
			uart_port_dtr_rts(uport, 1);
	}

	/*
	 * This is to allow setserial on this port. People may want to set
	 * port/irq/type and then reconfigure the port properly if it failed
	 * now.
	 */
	if (retval && capable(CAP_SYS_ADMIN))
		return 1;

	return retval;
}
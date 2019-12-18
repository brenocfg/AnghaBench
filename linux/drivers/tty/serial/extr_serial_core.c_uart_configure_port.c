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
struct uart_state {int dummy; } ;
struct uart_port {int flags; scalar_t__ type; int mctrl; TYPE_2__* cons; int /*<<< orphan*/  lock; TYPE_1__* ops; int /*<<< orphan*/  membase; int /*<<< orphan*/  mapbase; int /*<<< orphan*/  iobase; } ;
struct uart_driver {int dummy; } ;
struct TYPE_4__ {int flags; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* set_mctrl ) (struct uart_port*,int) ;int /*<<< orphan*/  (* config_port ) (struct uart_port*,unsigned int) ;} ;

/* Variables and functions */
 int CON_ENABLED ; 
 scalar_t__ PORT_UNKNOWN ; 
 int TIOCM_DTR ; 
 unsigned int UART_CONFIG_IRQ ; 
 unsigned int UART_CONFIG_TYPE ; 
 int /*<<< orphan*/  UART_PM_STATE_OFF ; 
 int /*<<< orphan*/  UART_PM_STATE_ON ; 
 int UPF_AUTO_IRQ ; 
 int UPF_BOOT_AUTOCONF ; 
 int UPF_FIXED_TYPE ; 
 int /*<<< orphan*/  register_console (TYPE_2__*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct uart_port*,unsigned int) ; 
 int /*<<< orphan*/  stub2 (struct uart_port*,int) ; 
 int /*<<< orphan*/  uart_change_pm (struct uart_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_console (struct uart_port*) ; 
 int /*<<< orphan*/  uart_report_port (struct uart_driver*,struct uart_port*) ; 

__attribute__((used)) static void
uart_configure_port(struct uart_driver *drv, struct uart_state *state,
		    struct uart_port *port)
{
	unsigned int flags;

	/*
	 * If there isn't a port here, don't do anything further.
	 */
	if (!port->iobase && !port->mapbase && !port->membase)
		return;

	/*
	 * Now do the auto configuration stuff.  Note that config_port
	 * is expected to claim the resources and map the port for us.
	 */
	flags = 0;
	if (port->flags & UPF_AUTO_IRQ)
		flags |= UART_CONFIG_IRQ;
	if (port->flags & UPF_BOOT_AUTOCONF) {
		if (!(port->flags & UPF_FIXED_TYPE)) {
			port->type = PORT_UNKNOWN;
			flags |= UART_CONFIG_TYPE;
		}
		port->ops->config_port(port, flags);
	}

	if (port->type != PORT_UNKNOWN) {
		unsigned long flags;

		uart_report_port(drv, port);

		/* Power up port for set_mctrl() */
		uart_change_pm(state, UART_PM_STATE_ON);

		/*
		 * Ensure that the modem control lines are de-activated.
		 * keep the DTR setting that is set in uart_set_options()
		 * We probably don't need a spinlock around this, but
		 */
		spin_lock_irqsave(&port->lock, flags);
		port->ops->set_mctrl(port, port->mctrl & TIOCM_DTR);
		spin_unlock_irqrestore(&port->lock, flags);

		/*
		 * If this driver supports console, and it hasn't been
		 * successfully registered yet, try to re-register it.
		 * It may be that the port was not available.
		 */
		if (port->cons && !(port->cons->flags & CON_ENABLED))
			register_console(port->cons);

		/*
		 * Power down all ports by default, except the
		 * console if we have one.
		 */
		if (!uart_console(port))
			uart_change_pm(state, UART_PM_STATE_OFF);
	}
}
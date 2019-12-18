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
struct tty_port {int /*<<< orphan*/  mutex; struct tty_struct* tty; } ;
struct uart_state {struct tty_port port; } ;
struct uart_port {int line; int /*<<< orphan*/  lock; int /*<<< orphan*/  mctrl; struct uart_ops* ops; TYPE_1__* cons; scalar_t__ suspended; int /*<<< orphan*/  irq; int /*<<< orphan*/  dev; } ;
struct uart_ops {int (* startup ) (struct uart_port*) ;int /*<<< orphan*/  (* start_tx ) (struct uart_port*) ;int /*<<< orphan*/  (* set_mctrl ) (struct uart_port*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* set_termios ) (struct uart_port*,struct ktermios*,int /*<<< orphan*/ *) ;} ;
struct uart_match {struct uart_driver* member_1; struct uart_port* member_0; } ;
struct uart_driver {struct uart_state* state; } ;
struct ktermios {scalar_t__ c_cflag; } ;
struct tty_struct {struct ktermios termios; } ;
struct device {int dummy; } ;
struct TYPE_2__ {scalar_t__ cflag; } ;

/* Variables and functions */
 int /*<<< orphan*/  UART_PM_STATE_ON ; 
 int /*<<< orphan*/  console_start (TYPE_1__*) ; 
 scalar_t__ console_suspend_enabled ; 
 struct device* device_find_child (int /*<<< orphan*/ ,struct uart_match*,int /*<<< orphan*/ ) ; 
 scalar_t__ device_may_wakeup (struct device*) ; 
 int /*<<< orphan*/  disable_irq_wake (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_get_irq_data (int /*<<< orphan*/ ) ; 
 scalar_t__ irqd_is_wakeup_set (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ktermios*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_device (struct device*) ; 
 int /*<<< orphan*/  serial_match_port ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct uart_port*,struct ktermios*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (struct uart_port*,int /*<<< orphan*/ ) ; 
 int stub3 (struct uart_port*) ; 
 int /*<<< orphan*/  stub4 (struct uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (struct uart_port*) ; 
 int /*<<< orphan*/  tty_port_set_initialized (struct tty_port*,int) ; 
 int /*<<< orphan*/  tty_port_set_suspended (struct tty_port*,int /*<<< orphan*/ ) ; 
 scalar_t__ tty_port_suspended (struct tty_port*) ; 
 int /*<<< orphan*/  uart_change_pm (struct uart_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_change_speed (struct tty_struct*,struct uart_state*,int /*<<< orphan*/ *) ; 
 scalar_t__ uart_console (struct uart_port*) ; 
 int /*<<< orphan*/  uart_shutdown (struct tty_struct*,struct uart_state*) ; 

int uart_resume_port(struct uart_driver *drv, struct uart_port *uport)
{
	struct uart_state *state = drv->state + uport->line;
	struct tty_port *port = &state->port;
	struct device *tty_dev;
	struct uart_match match = {uport, drv};
	struct ktermios termios;

	mutex_lock(&port->mutex);

	tty_dev = device_find_child(uport->dev, &match, serial_match_port);
	if (!uport->suspended && device_may_wakeup(tty_dev)) {
		if (irqd_is_wakeup_set(irq_get_irq_data((uport->irq))))
			disable_irq_wake(uport->irq);
		put_device(tty_dev);
		mutex_unlock(&port->mutex);
		return 0;
	}
	put_device(tty_dev);
	uport->suspended = 0;

	/*
	 * Re-enable the console device after suspending.
	 */
	if (uart_console(uport)) {
		/*
		 * First try to use the console cflag setting.
		 */
		memset(&termios, 0, sizeof(struct ktermios));
		termios.c_cflag = uport->cons->cflag;

		/*
		 * If that's unset, use the tty termios setting.
		 */
		if (port->tty && termios.c_cflag == 0)
			termios = port->tty->termios;

		if (console_suspend_enabled)
			uart_change_pm(state, UART_PM_STATE_ON);
		uport->ops->set_termios(uport, &termios, NULL);
		if (console_suspend_enabled)
			console_start(uport->cons);
	}

	if (tty_port_suspended(port)) {
		const struct uart_ops *ops = uport->ops;
		int ret;

		uart_change_pm(state, UART_PM_STATE_ON);
		spin_lock_irq(&uport->lock);
		ops->set_mctrl(uport, 0);
		spin_unlock_irq(&uport->lock);
		if (console_suspend_enabled || !uart_console(uport)) {
			/* Protected by port mutex for now */
			struct tty_struct *tty = port->tty;
			ret = ops->startup(uport);
			if (ret == 0) {
				if (tty)
					uart_change_speed(tty, state, NULL);
				spin_lock_irq(&uport->lock);
				ops->set_mctrl(uport, uport->mctrl);
				ops->start_tx(uport);
				spin_unlock_irq(&uport->lock);
				tty_port_set_initialized(port, 1);
			} else {
				/*
				 * Failed to resume - maybe hardware went away?
				 * Clear the "initialized" flag so we won't try
				 * to call the low level drivers shutdown method.
				 */
				uart_shutdown(tty, state);
			}
		}

		tty_port_set_suspended(port, 0);
	}

	mutex_unlock(&port->mutex);

	return 0;
}
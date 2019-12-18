#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * dev; int /*<<< orphan*/  type; int /*<<< orphan*/  flags; int /*<<< orphan*/  lock; } ;
struct uart_8250_port {TYPE_1__ port; scalar_t__ capabilities; scalar_t__ em485; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  PORT_UNKNOWN ; 
 int /*<<< orphan*/  UPF_BOOT_AUTOCONF ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  serial8250_apply_quirks (struct uart_8250_port*) ; 
 int /*<<< orphan*/  serial8250_em485_destroy (struct uart_8250_port*) ; 
 TYPE_3__* serial8250_isa_devs ; 
 struct uart_8250_port* serial8250_ports ; 
 int /*<<< orphan*/  serial8250_reg ; 
 int /*<<< orphan*/  serial_mutex ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  uart_add_one_port (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  uart_remove_one_port (int /*<<< orphan*/ *,TYPE_1__*) ; 

void serial8250_unregister_port(int line)
{
	struct uart_8250_port *uart = &serial8250_ports[line];

	mutex_lock(&serial_mutex);

	if (uart->em485) {
		unsigned long flags;

		spin_lock_irqsave(&uart->port.lock, flags);
		serial8250_em485_destroy(uart);
		spin_unlock_irqrestore(&uart->port.lock, flags);
	}

	uart_remove_one_port(&serial8250_reg, &uart->port);
	if (serial8250_isa_devs) {
		uart->port.flags &= ~UPF_BOOT_AUTOCONF;
		uart->port.type = PORT_UNKNOWN;
		uart->port.dev = &serial8250_isa_devs->dev;
		uart->capabilities = 0;
		serial8250_apply_quirks(uart);
		uart_add_one_port(&serial8250_reg, &uart->port);
	} else {
		uart->port.dev = NULL;
	}
	mutex_unlock(&serial_mutex);
}
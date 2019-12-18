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
struct TYPE_2__ {int /*<<< orphan*/  mutex; } ;
struct sdio_uart_port {size_t index; TYPE_1__ port; int /*<<< orphan*/  func_lock; struct sdio_func* func; } ;
struct sdio_func {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sdio_claim_host (struct sdio_func*) ; 
 int /*<<< orphan*/  sdio_disable_func (struct sdio_func*) ; 
 int /*<<< orphan*/  sdio_release_host (struct sdio_func*) ; 
 int /*<<< orphan*/  sdio_release_irq (struct sdio_func*) ; 
 int /*<<< orphan*/  sdio_uart_port_put (struct sdio_uart_port*) ; 
 int /*<<< orphan*/ ** sdio_uart_table ; 
 int /*<<< orphan*/  sdio_uart_table_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_port_tty_hangup (TYPE_1__*,int) ; 

__attribute__((used)) static void sdio_uart_port_remove(struct sdio_uart_port *port)
{
	struct sdio_func *func;

	spin_lock(&sdio_uart_table_lock);
	sdio_uart_table[port->index] = NULL;
	spin_unlock(&sdio_uart_table_lock);

	/*
	 * We're killing a port that potentially still is in use by
	 * the tty layer. Be careful to prevent any further access
	 * to the SDIO function and arrange for the tty layer to
	 * give up on that port ASAP.
	 * Beware: the lock ordering is critical.
	 */
	mutex_lock(&port->port.mutex);
	mutex_lock(&port->func_lock);
	func = port->func;
	sdio_claim_host(func);
	port->func = NULL;
	mutex_unlock(&port->func_lock);
	/* tty_hangup is async so is this safe as is ?? */
	tty_port_tty_hangup(&port->port, false);
	mutex_unlock(&port->port.mutex);
	sdio_release_irq(func);
	sdio_disable_func(func);
	sdio_release_host(func);

	sdio_uart_port_put(port);
}
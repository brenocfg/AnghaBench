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
struct uart_port {int /*<<< orphan*/  irq; } ;
struct TYPE_2__ {scalar_t__ tail; scalar_t__ head; } ;
struct atmel_uart_port {TYPE_1__ rx_ring; int /*<<< orphan*/  (* release_tx ) (struct uart_port*) ;int /*<<< orphan*/  (* release_rx ) (struct uart_port*) ;int /*<<< orphan*/  tasklet_tx; int /*<<< orphan*/  tasklet_rx; int /*<<< orphan*/  uart_timer; int /*<<< orphan*/  tasklet_shutdown; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATMEL_US_CR ; 
 int /*<<< orphan*/  ATMEL_US_IDR ; 
 int ATMEL_US_RSTSTA ; 
 int /*<<< orphan*/  atmel_disable_ms (struct uart_port*) ; 
 int /*<<< orphan*/  atmel_flush_buffer (struct uart_port*) ; 
 int /*<<< orphan*/  atmel_stop_rx (struct uart_port*) ; 
 int /*<<< orphan*/  atmel_stop_tx (struct uart_port*) ; 
 int /*<<< orphan*/  atmel_uart_writel (struct uart_port*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct uart_port*) ; 
 int /*<<< orphan*/  stub1 (struct uart_port*) ; 
 int /*<<< orphan*/  stub2 (struct uart_port*) ; 
 int /*<<< orphan*/  synchronize_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 
 struct atmel_uart_port* to_atmel_uart_port (struct uart_port*) ; 

__attribute__((used)) static void atmel_shutdown(struct uart_port *port)
{
	struct atmel_uart_port *atmel_port = to_atmel_uart_port(port);

	/* Disable modem control lines interrupts */
	atmel_disable_ms(port);

	/* Disable interrupts at device level */
	atmel_uart_writel(port, ATMEL_US_IDR, -1);

	/* Prevent spurious interrupts from scheduling the tasklet */
	atomic_inc(&atmel_port->tasklet_shutdown);

	/*
	 * Prevent any tasklets being scheduled during
	 * cleanup
	 */
	del_timer_sync(&atmel_port->uart_timer);

	/* Make sure that no interrupt is on the fly */
	synchronize_irq(port->irq);

	/*
	 * Clear out any scheduled tasklets before
	 * we destroy the buffers
	 */
	tasklet_kill(&atmel_port->tasklet_rx);
	tasklet_kill(&atmel_port->tasklet_tx);

	/*
	 * Ensure everything is stopped and
	 * disable port and break condition.
	 */
	atmel_stop_rx(port);
	atmel_stop_tx(port);

	atmel_uart_writel(port, ATMEL_US_CR, ATMEL_US_RSTSTA);

	/*
	 * Shut-down the DMA.
	 */
	if (atmel_port->release_rx)
		atmel_port->release_rx(port);
	if (atmel_port->release_tx)
		atmel_port->release_tx(port);

	/*
	 * Reset ring buffer pointers
	 */
	atmel_port->rx_ring.head = 0;
	atmel_port->rx_ring.tail = 0;

	/*
	 * Free the interrupts
	 */
	free_irq(port->irq, port);

	atmel_flush_buffer(port);
}
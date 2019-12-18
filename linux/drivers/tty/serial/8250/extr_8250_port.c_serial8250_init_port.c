#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct uart_port {int /*<<< orphan*/ * ops; int /*<<< orphan*/  lock; } ;
struct uart_8250_port {int cur_iotype; struct uart_port port; } ;

/* Variables and functions */
 int /*<<< orphan*/  serial8250_pops ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

void serial8250_init_port(struct uart_8250_port *up)
{
	struct uart_port *port = &up->port;

	spin_lock_init(&port->lock);
	port->ops = &serial8250_pops;

	up->cur_iotype = 0xFF;
}
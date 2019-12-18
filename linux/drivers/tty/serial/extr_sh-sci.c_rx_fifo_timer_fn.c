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
struct uart_port {int /*<<< orphan*/  dev; } ;
struct timer_list {int dummy; } ;
struct sci_port {struct uart_port port; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 struct sci_port* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rx_fifo_timer ; 
 struct sci_port* s ; 
 int /*<<< orphan*/  scif_set_rtrg (struct uart_port*,int) ; 

__attribute__((used)) static void rx_fifo_timer_fn(struct timer_list *t)
{
	struct sci_port *s = from_timer(s, t, rx_fifo_timer);
	struct uart_port *port = &s->port;

	dev_dbg(port->dev, "Rx timed out\n");
	scif_set_rtrg(port, 1);
}
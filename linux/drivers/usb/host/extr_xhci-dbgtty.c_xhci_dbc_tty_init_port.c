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
struct xhci_hcd {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * ops; } ;
struct dbc_port {scalar_t__ n_read; TYPE_1__ port; int /*<<< orphan*/  out; int /*<<< orphan*/  in; int /*<<< orphan*/  write_pool; int /*<<< orphan*/  read_queue; int /*<<< orphan*/  read_pool; int /*<<< orphan*/  push; int /*<<< orphan*/  port_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dbc_port_ops ; 
 int /*<<< orphan*/  dbc_rx_push ; 
 int /*<<< orphan*/  get_in_ep (struct xhci_hcd*) ; 
 int /*<<< orphan*/  get_out_ep (struct xhci_hcd*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  tty_port_init (TYPE_1__*) ; 

__attribute__((used)) static void
xhci_dbc_tty_init_port(struct xhci_hcd *xhci, struct dbc_port *port)
{
	tty_port_init(&port->port);
	spin_lock_init(&port->port_lock);
	tasklet_init(&port->push, dbc_rx_push, (unsigned long)port);
	INIT_LIST_HEAD(&port->read_pool);
	INIT_LIST_HEAD(&port->read_queue);
	INIT_LIST_HEAD(&port->write_pool);

	port->in =		get_in_ep(xhci);
	port->out =		get_out_ep(xhci);
	port->port.ops =	&dbc_port_ops;
	port->n_read =		0;
}
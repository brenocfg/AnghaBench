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
struct dbc_port {int /*<<< orphan*/  port; int /*<<< orphan*/  push; } ;

/* Variables and functions */
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_port_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
xhci_dbc_tty_exit_port(struct dbc_port *port)
{
	tasklet_kill(&port->push);
	tty_port_destroy(&port->port);
}
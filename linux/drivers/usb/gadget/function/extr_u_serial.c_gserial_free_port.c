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
struct gs_port {int /*<<< orphan*/  port; int /*<<< orphan*/ * port_usb; int /*<<< orphan*/  close_wait; int /*<<< orphan*/  push; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gs_closed (struct gs_port*) ; 
 int /*<<< orphan*/  kfree (struct gs_port*) ; 
 int /*<<< orphan*/  tty_port_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gserial_free_port(struct gs_port *port)
{
	cancel_delayed_work_sync(&port->push);
	/* wait for old opens to finish */
	wait_event(port->close_wait, gs_closed(port));
	WARN_ON(port->port_usb != NULL);
	tty_port_destroy(&port->port);
	kfree(port);
}
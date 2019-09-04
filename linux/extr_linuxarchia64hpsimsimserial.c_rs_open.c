#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tty_struct {int index; struct serial_state* driver_data; } ;
struct tty_port {int low_latency; int flags; } ;
struct serial_state {struct tty_port port; } ;
struct file {int dummy; } ;
struct TYPE_3__ {int flags; struct TYPE_3__* next; scalar_t__ write; } ;

/* Variables and functions */
 int ASYNC_LOW_LATENCY ; 
 int CON_ENABLED ; 
 TYPE_1__* console ; 
 TYPE_1__* console_drivers ; 
 struct serial_state* rs_table ; 
 int tty_port_open (struct tty_port*,struct tty_struct*,struct file*) ; 

__attribute__((used)) static int rs_open(struct tty_struct *tty, struct file * filp)
{
	struct serial_state *info = rs_table + tty->index;
	struct tty_port *port = &info->port;

	tty->driver_data = info;
	port->low_latency = (port->flags & ASYNC_LOW_LATENCY) ? 1 : 0;

	/*
	 * figure out which console to use (should be one already)
	 */
	console = console_drivers;
	while (console) {
		if ((console->flags & CON_ENABLED) && console->write) break;
		console = console->next;
	}

	return tty_port_open(port, tty, filp);
}
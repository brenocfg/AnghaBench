#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tty_struct {struct fwtty_port* driver_data; } ;
struct serial_struct {int baud_base; int /*<<< orphan*/  close_delay; int /*<<< orphan*/  xmit_fifo_size; int /*<<< orphan*/  flags; int /*<<< orphan*/  line; int /*<<< orphan*/  type; } ;
struct TYPE_4__ {int /*<<< orphan*/  mutex; int /*<<< orphan*/  close_delay; int /*<<< orphan*/  flags; TYPE_1__* tty; } ;
struct fwtty_port {TYPE_2__ port; } ;
struct TYPE_3__ {int /*<<< orphan*/  index; } ;

/* Variables and functions */
 int /*<<< orphan*/  FWTTY_PORT_TXFIFO_LEN ; 
 int /*<<< orphan*/  PORT_UNKNOWN ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int get_serial_info(struct tty_struct *tty,
			   struct serial_struct *ss)
{
	struct fwtty_port *port = tty->driver_data;

	mutex_lock(&port->port.mutex);
	ss->type =  PORT_UNKNOWN;
	ss->line =  port->port.tty->index;
	ss->flags = port->port.flags;
	ss->xmit_fifo_size = FWTTY_PORT_TXFIFO_LEN;
	ss->baud_base = 400000000;
	ss->close_delay = port->port.close_delay;
	mutex_unlock(&port->port.mutex);
	return 0;
}
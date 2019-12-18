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
struct tty_struct {int /*<<< orphan*/  index; struct mxser_port* driver_data; } ;
struct tty_port {int /*<<< orphan*/  mutex; int /*<<< orphan*/  closing_wait; int /*<<< orphan*/  close_delay; int /*<<< orphan*/  flags; } ;
struct serial_struct {int /*<<< orphan*/  custom_divisor; int /*<<< orphan*/  closing_wait; int /*<<< orphan*/  close_delay; int /*<<< orphan*/  baud_base; int /*<<< orphan*/  flags; int /*<<< orphan*/  irq; int /*<<< orphan*/  port; int /*<<< orphan*/  line; int /*<<< orphan*/  type; } ;
struct mxser_port {int /*<<< orphan*/  custom_divisor; struct tty_port port; int /*<<< orphan*/  baud_base; TYPE_1__* board; int /*<<< orphan*/  ioaddr; int /*<<< orphan*/  type; } ;
struct TYPE_2__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int ENOTTY ; 
 int /*<<< orphan*/  MXSER_PORTS ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mxser_get_serial_info(struct tty_struct *tty,
		struct serial_struct *ss)
{
	struct mxser_port *info = tty->driver_data;
	struct tty_port *port = &info->port;

	if (tty->index == MXSER_PORTS)
		return -ENOTTY;

	mutex_lock(&port->mutex);
	ss->type = info->type,
	ss->line = tty->index,
	ss->port = info->ioaddr,
	ss->irq = info->board->irq,
	ss->flags = info->port.flags,
	ss->baud_base = info->baud_base,
	ss->close_delay = info->port.close_delay,
	ss->closing_wait = info->port.closing_wait,
	ss->custom_divisor = info->custom_divisor,
	mutex_unlock(&port->mutex);
	return 0;
}
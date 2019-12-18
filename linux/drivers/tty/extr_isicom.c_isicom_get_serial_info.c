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
struct tty_struct {int /*<<< orphan*/  name; struct isi_port* driver_data; } ;
struct serial_struct {int /*<<< orphan*/  closing_wait; int /*<<< orphan*/  close_delay; int /*<<< orphan*/  flags; int /*<<< orphan*/  irq; int /*<<< orphan*/  port; struct isi_port* line; } ;
struct TYPE_4__ {int /*<<< orphan*/  mutex; int /*<<< orphan*/  closing_wait; int /*<<< orphan*/  close_delay; int /*<<< orphan*/  flags; } ;
struct isi_port {TYPE_2__ port; TYPE_1__* card; } ;
struct TYPE_3__ {int /*<<< orphan*/  irq; int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int ENODEV ; 
 int isi_ports ; 
 scalar_t__ isicom_paranoia_check (struct isi_port*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int isicom_get_serial_info(struct tty_struct *tty,
	struct serial_struct *ss)
{
	struct isi_port *port = tty->driver_data;

	if (isicom_paranoia_check(port, tty->name, "isicom_ioctl"))
		return -ENODEV;

	mutex_lock(&port->port.mutex);
/*	ss->type = ? */
	ss->line = port - isi_ports;
	ss->port = port->card->base;
	ss->irq = port->card->irq;
	ss->flags = port->port.flags;
/*	ss->baud_base = ? */
	ss->close_delay = port->port.close_delay;
	ss->closing_wait = port->port.closing_wait;
	mutex_unlock(&port->port.mutex);
	return 0;
}
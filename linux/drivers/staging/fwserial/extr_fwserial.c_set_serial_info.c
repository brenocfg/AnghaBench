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
struct tty_struct {struct fwtty_port* driver_data; } ;
struct serial_struct {scalar_t__ irq; scalar_t__ port; scalar_t__ custom_divisor; int baud_base; int flags; int close_delay; } ;
struct TYPE_2__ {int flags; int close_delay; int /*<<< orphan*/  mutex; } ;
struct fwtty_port {TYPE_1__ port; } ;

/* Variables and functions */
 int ASYNC_USR_MASK ; 
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int EPERM ; 
 int HZ ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int set_serial_info(struct tty_struct *tty,
			   struct serial_struct *ss)
{
	struct fwtty_port *port = tty->driver_data;

	if (ss->irq != 0 || ss->port != 0 || ss->custom_divisor != 0 ||
	    ss->baud_base != 400000000)
		return -EPERM;

	mutex_lock(&port->port.mutex);
	if (!capable(CAP_SYS_ADMIN)) {
		if (((ss->flags & ~ASYNC_USR_MASK) !=
		     (port->port.flags & ~ASYNC_USR_MASK))) {
			mutex_unlock(&port->port.mutex);
			return -EPERM;
		}
	}
	port->port.close_delay = ss->close_delay * HZ / 100;
	mutex_unlock(&port->port.mutex);

	return 0;
}
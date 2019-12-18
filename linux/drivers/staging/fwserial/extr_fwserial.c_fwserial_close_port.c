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
struct tty_struct {int dummy; } ;
struct tty_driver {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  mutex; } ;
struct fwtty_port {int /*<<< orphan*/  index; TYPE_1__ port; } ;

/* Variables and functions */
 struct tty_driver* fwloop_driver ; 
 int /*<<< orphan*/  loop_idx (struct fwtty_port*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_kref_put (struct tty_struct*) ; 
 struct tty_struct* tty_port_tty_get (TYPE_1__*) ; 
 int /*<<< orphan*/  tty_unregister_device (struct tty_driver*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_vhangup (struct tty_struct*) ; 

__attribute__((used)) static void fwserial_close_port(struct tty_driver *driver,
				struct fwtty_port *port)
{
	struct tty_struct *tty;

	mutex_lock(&port->port.mutex);
	tty = tty_port_tty_get(&port->port);
	if (tty) {
		tty_vhangup(tty);
		tty_kref_put(tty);
	}
	mutex_unlock(&port->port.mutex);

	if (driver == fwloop_driver)
		tty_unregister_device(driver, loop_idx(port));
	else
		tty_unregister_device(driver, port->index);
}
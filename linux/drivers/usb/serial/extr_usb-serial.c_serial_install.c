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
struct usb_serial_port {struct usb_serial* serial; } ;
struct usb_serial {int /*<<< orphan*/  disc_mutex; TYPE_2__* type; int /*<<< orphan*/  interface; } ;
struct tty_struct {int index; struct usb_serial_port* driver_data; } ;
struct tty_driver {int /*<<< orphan*/ ** termios; } ;
struct TYPE_3__ {int /*<<< orphan*/  owner; } ;
struct TYPE_4__ {TYPE_1__ driver; int /*<<< orphan*/  (* init_termios ) (struct tty_struct*) ;} ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct tty_struct*) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 
 int tty_standard_install (struct tty_driver*,struct tty_struct*) ; 
 int usb_autopm_get_interface (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_autopm_put_interface (int /*<<< orphan*/ ) ; 
 struct usb_serial_port* usb_serial_port_get_by_minor (int) ; 
 int /*<<< orphan*/  usb_serial_put (struct usb_serial*) ; 

__attribute__((used)) static int serial_install(struct tty_driver *driver, struct tty_struct *tty)
{
	int idx = tty->index;
	struct usb_serial *serial;
	struct usb_serial_port *port;
	bool init_termios;
	int retval = -ENODEV;

	port = usb_serial_port_get_by_minor(idx);
	if (!port)
		return retval;

	serial = port->serial;
	if (!try_module_get(serial->type->driver.owner))
		goto error_module_get;

	retval = usb_autopm_get_interface(serial->interface);
	if (retval)
		goto error_get_interface;

	init_termios = (driver->termios[idx] == NULL);

	retval = tty_standard_install(driver, tty);
	if (retval)
		goto error_init_termios;

	mutex_unlock(&serial->disc_mutex);

	/* allow the driver to update the initial settings */
	if (init_termios && serial->type->init_termios)
		serial->type->init_termios(tty);

	tty->driver_data = port;

	return retval;

 error_init_termios:
	usb_autopm_put_interface(serial->interface);
 error_get_interface:
	module_put(serial->type->driver.owner);
 error_module_get:
	usb_serial_put(serial);
	mutex_unlock(&serial->disc_mutex);
	return retval;
}
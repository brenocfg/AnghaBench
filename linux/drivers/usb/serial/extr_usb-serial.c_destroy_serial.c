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
struct usb_serial_port {int /*<<< orphan*/  dev; int /*<<< orphan*/ * serial; } ;
struct usb_serial {int num_port_pointers; int /*<<< orphan*/  dev; int /*<<< orphan*/  interface; struct usb_serial_port** port; TYPE_1__* type; scalar_t__ attached; scalar_t__ minors_reserved; } ;
struct kref {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* release ) (struct usb_serial*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct usb_serial*) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_minors (struct usb_serial*) ; 
 int /*<<< orphan*/  stub1 (struct usb_serial*) ; 
 struct usb_serial* to_usb_serial (struct kref*) ; 
 int /*<<< orphan*/  usb_put_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_put_intf (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void destroy_serial(struct kref *kref)
{
	struct usb_serial *serial;
	struct usb_serial_port *port;
	int i;

	serial = to_usb_serial(kref);

	/* return the minor range that this device had */
	if (serial->minors_reserved)
		release_minors(serial);

	if (serial->attached && serial->type->release)
		serial->type->release(serial);

	/* Now that nothing is using the ports, they can be freed */
	for (i = 0; i < serial->num_port_pointers; ++i) {
		port = serial->port[i];
		if (port) {
			port->serial = NULL;
			put_device(&port->dev);
		}
	}

	usb_put_intf(serial->interface);
	usb_put_dev(serial->dev);
	kfree(serial);
}
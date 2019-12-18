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
struct usb_serial_port {struct usb_serial* serial; } ;
struct usb_serial {int /*<<< orphan*/  kref; int /*<<< orphan*/  disc_mutex; scalar_t__ disconnected; } ;

/* Variables and functions */
 struct usb_serial_port* idr_find (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  serial_minors ; 
 int /*<<< orphan*/  table_lock ; 

struct usb_serial_port *usb_serial_port_get_by_minor(unsigned minor)
{
	struct usb_serial *serial;
	struct usb_serial_port *port;

	mutex_lock(&table_lock);
	port = idr_find(&serial_minors, minor);
	if (!port)
		goto exit;

	serial = port->serial;
	mutex_lock(&serial->disc_mutex);
	if (serial->disconnected) {
		mutex_unlock(&serial->disc_mutex);
		port = NULL;
	} else {
		kref_get(&serial->kref);
	}
exit:
	mutex_unlock(&table_lock);
	return port;
}
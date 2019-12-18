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
struct TYPE_2__ {int drain_delay; } ;
struct usb_serial_port {TYPE_1__ port; int /*<<< orphan*/  serial; } ;
struct usb_device_id {int /*<<< orphan*/  driver_info; } ;
struct spcp8x5_private {int /*<<< orphan*/  quirks; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct spcp8x5_private* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 struct usb_device_id* usb_get_serial_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_set_serial_port_data (struct usb_serial_port*,struct spcp8x5_private*) ; 

__attribute__((used)) static int spcp8x5_port_probe(struct usb_serial_port *port)
{
	const struct usb_device_id *id = usb_get_serial_data(port->serial);
	struct spcp8x5_private *priv;

	priv = kzalloc(sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	spin_lock_init(&priv->lock);
	priv->quirks = id->driver_info;

	usb_set_serial_port_data(port, priv);

	port->port.drain_delay = 256;

	return 0;
}
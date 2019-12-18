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
struct usb_serial_port {TYPE_1__ port; } ;
struct oti6858_private {int /*<<< orphan*/  delayed_write_work; int /*<<< orphan*/  delayed_setup_work; struct usb_serial_port* port; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct oti6858_private* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_data ; 
 int /*<<< orphan*/  setup_line ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_set_serial_port_data (struct usb_serial_port*,struct oti6858_private*) ; 

__attribute__((used)) static int oti6858_port_probe(struct usb_serial_port *port)
{
	struct oti6858_private *priv;

	priv = kzalloc(sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	spin_lock_init(&priv->lock);
	priv->port = port;
	INIT_DELAYED_WORK(&priv->delayed_setup_work, setup_line);
	INIT_DELAYED_WORK(&priv->delayed_write_work, send_data);

	usb_set_serial_port_data(port, priv);

	port->port.drain_delay = 256;	/* FIXME: check the FIFO length */

	return 0;
}
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
struct usb_serial_port {int /*<<< orphan*/  serial; } ;
struct keyspan_pda_private {struct usb_serial_port* port; int /*<<< orphan*/  serial; int /*<<< orphan*/  unthrottle_work; int /*<<< orphan*/  wakeup_work; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  keyspan_pda_request_unthrottle ; 
 int /*<<< orphan*/  keyspan_pda_wakeup_write ; 
 struct keyspan_pda_private* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_set_serial_port_data (struct usb_serial_port*,struct keyspan_pda_private*) ; 

__attribute__((used)) static int keyspan_pda_port_probe(struct usb_serial_port *port)
{

	struct keyspan_pda_private *priv;

	priv = kmalloc(sizeof(struct keyspan_pda_private), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	INIT_WORK(&priv->wakeup_work, keyspan_pda_wakeup_write);
	INIT_WORK(&priv->unthrottle_work, keyspan_pda_request_unthrottle);
	priv->serial = port->serial;
	priv->port = port;

	usb_set_serial_port_data(port, priv);

	return 0;
}
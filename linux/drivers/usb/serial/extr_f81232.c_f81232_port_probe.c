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
struct f81232_private {struct usb_serial_port* port; int /*<<< orphan*/  lsr_work; int /*<<< orphan*/  interrupt_work; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f81232_interrupt_work ; 
 int /*<<< orphan*/  f81232_lsr_worker ; 
 struct f81232_private* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_set_serial_port_data (struct usb_serial_port*,struct f81232_private*) ; 

__attribute__((used)) static int f81232_port_probe(struct usb_serial_port *port)
{
	struct f81232_private *priv;

	priv = kzalloc(sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	mutex_init(&priv->lock);
	INIT_WORK(&priv->interrupt_work,  f81232_interrupt_work);
	INIT_WORK(&priv->lsr_work, f81232_lsr_worker);

	usb_set_serial_port_data(port, priv);

	port->port.drain_delay = 256;
	priv->port = port;

	return 0;
}
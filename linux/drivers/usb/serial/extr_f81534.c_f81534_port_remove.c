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
struct usb_serial_port {int dummy; } ;
struct f81534_port_private {int /*<<< orphan*/  lsr_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  flush_work (int /*<<< orphan*/ *) ; 
 struct f81534_port_private* usb_get_serial_port_data (struct usb_serial_port*) ; 

__attribute__((used)) static int f81534_port_remove(struct usb_serial_port *port)
{
	struct f81534_port_private *port_priv = usb_get_serial_port_data(port);

	flush_work(&port_priv->lsr_work);
	return 0;
}
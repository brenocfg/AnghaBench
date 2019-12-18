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
struct iuu_private {struct iuu_private* buf; struct iuu_private* writebuf; } ;

/* Variables and functions */
 int /*<<< orphan*/  iuu_remove_sysfs_attrs (struct usb_serial_port*) ; 
 int /*<<< orphan*/  kfree (struct iuu_private*) ; 
 struct iuu_private* usb_get_serial_port_data (struct usb_serial_port*) ; 

__attribute__((used)) static int iuu_port_remove(struct usb_serial_port *port)
{
	struct iuu_private *priv = usb_get_serial_port_data(port);

	iuu_remove_sysfs_attrs(port);
	kfree(priv->writebuf);
	kfree(priv->buf);
	kfree(priv);

	return 0;
}
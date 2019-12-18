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
struct usb_interface {int /*<<< orphan*/  dev; } ;
struct parport_uss720_private {int /*<<< orphan*/  ref_count; int /*<<< orphan*/ * pp; int /*<<< orphan*/ * usbdev; } ;
struct parport {struct parport_uss720_private* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  destroy_priv ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  kill_all_async_requests_priv (struct parport_uss720_private*) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parport_put_port (struct parport*) ; 
 int /*<<< orphan*/  parport_remove_port (struct parport*) ; 
 struct parport* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void uss720_disconnect(struct usb_interface *intf)
{
	struct parport *pp = usb_get_intfdata(intf);
	struct parport_uss720_private *priv;

	dev_dbg(&intf->dev, "disconnect\n");
	usb_set_intfdata(intf, NULL);
	if (pp) {
		priv = pp->private_data;
		priv->usbdev = NULL;
		priv->pp = NULL;
		dev_dbg(&intf->dev, "parport_remove_port\n");
		parport_remove_port(pp);
		parport_put_port(pp);
		kill_all_async_requests_priv(priv);
		kref_put(&priv->ref_count, destroy_priv);
	}
	dev_dbg(&intf->dev, "disconnect done\n");
}
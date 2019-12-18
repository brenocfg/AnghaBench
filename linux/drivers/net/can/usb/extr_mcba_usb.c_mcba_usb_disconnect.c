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
struct usb_interface {int dummy; } ;
struct mcba_priv {int /*<<< orphan*/  netdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_candev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mcba_urb_unlink (struct mcba_priv*) ; 
 int /*<<< orphan*/  netdev_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  unregister_candev (int /*<<< orphan*/ ) ; 
 struct mcba_priv* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mcba_usb_disconnect(struct usb_interface *intf)
{
	struct mcba_priv *priv = usb_get_intfdata(intf);

	usb_set_intfdata(intf, NULL);

	netdev_info(priv->netdev, "device disconnected\n");

	unregister_candev(priv->netdev);
	mcba_urb_unlink(priv);
	free_candev(priv->netdev);
}
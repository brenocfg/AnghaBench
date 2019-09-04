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
struct ucan_priv {int /*<<< orphan*/  netdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_candev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_netdev (int /*<<< orphan*/ ) ; 
 struct ucan_priv* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ucan_disconnect(struct usb_interface *intf)
{
	struct ucan_priv *up = usb_get_intfdata(intf);

	usb_set_intfdata(intf, NULL);

	if (up) {
		unregister_netdev(up->netdev);
		free_candev(up->netdev);
	}
}
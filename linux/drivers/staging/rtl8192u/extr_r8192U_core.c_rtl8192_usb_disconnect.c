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
struct r8192_priv {int /*<<< orphan*/ * pFirmware; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_DOWN ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free_ieee80211 (struct net_device*) ; 
 struct r8192_priv* ieee80211_priv (struct net_device*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtl8192_down (struct net_device*) ; 
 int /*<<< orphan*/  rtl8192_proc_remove_one (struct net_device*) ; 
 int /*<<< orphan*/  rtl8192_usb_deleteendpoints (struct net_device*) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 
 struct net_device* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void rtl8192_usb_disconnect(struct usb_interface *intf)
{
	struct net_device *dev = usb_get_intfdata(intf);
	struct r8192_priv *priv = ieee80211_priv(dev);

	unregister_netdev(dev);

	RT_TRACE(COMP_DOWN, "=============>wlan driver to be removed\n");
	rtl8192_proc_remove_one(dev);

	rtl8192_down(dev);
	kfree(priv->pFirmware);
	priv->pFirmware = NULL;
	rtl8192_usb_deleteendpoints(dev);
	usleep_range(10000, 11000);
	free_ieee80211(dev);

	RT_TRACE(COMP_DOWN, "wlan driver removed\n");
}
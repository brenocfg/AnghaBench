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
struct rtl8187_priv {int /*<<< orphan*/  io_dmabuf; int /*<<< orphan*/  udev; } ;
struct ieee80211_hw {struct rtl8187_priv* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  ieee80211_free_hw (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  ieee80211_unregister_hw (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  interface_to_usbdev (struct usb_interface*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl8187_leds_exit (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl8187_rfkill_exit (struct ieee80211_hw*) ; 
 struct ieee80211_hw* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_put_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_reset_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rtl8187_disconnect(struct usb_interface *intf)
{
	struct ieee80211_hw *dev = usb_get_intfdata(intf);
	struct rtl8187_priv *priv;

	if (!dev)
		return;

#ifdef CONFIG_RTL8187_LEDS
	rtl8187_leds_exit(dev);
#endif
	rtl8187_rfkill_exit(dev);
	ieee80211_unregister_hw(dev);

	priv = dev->priv;
	usb_reset_device(priv->udev);
	usb_put_dev(interface_to_usbdev(intf));
	kfree(priv->io_dmabuf);
	ieee80211_free_hw(dev);
}
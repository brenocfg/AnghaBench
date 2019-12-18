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
struct usb_interface {int dummy; } ;
struct usb_device {scalar_t__ state; } ;
struct net_device {int dummy; } ;
struct _adapter {int surprise_removed; int /*<<< orphan*/  rtl8712_fw_ready; int /*<<< orphan*/  fw; } ;
struct TYPE_2__ {scalar_t__ drv_registered; } ;

/* Variables and functions */
 scalar_t__ USB_STATE_NOTATTACHED ; 
 TYPE_1__ drvpriv ; 
 int /*<<< orphan*/  flush_scheduled_work () ; 
 struct usb_device* interface_to_usbdev (struct usb_interface*) ; 
 struct _adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  r8712_free_drv_sw (struct _adapter*) ; 
 int /*<<< orphan*/  r8712_stop_drv_timers (struct _adapter*) ; 
 int /*<<< orphan*/  r871x_dev_unload (struct _adapter*) ; 
 int /*<<< orphan*/  release_firmware (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 
 struct net_device* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_put_dev (struct usb_device*) ; 
 int /*<<< orphan*/  usb_reset_device (struct usb_device*) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void r871xu_dev_remove(struct usb_interface *pusb_intf)
{
	struct net_device *pnetdev = usb_get_intfdata(pusb_intf);
	struct usb_device *udev = interface_to_usbdev(pusb_intf);

	if (pnetdev) {
		struct _adapter *padapter = netdev_priv(pnetdev);

		usb_set_intfdata(pusb_intf, NULL);
		release_firmware(padapter->fw);
		/* never exit with a firmware callback pending */
		wait_for_completion(&padapter->rtl8712_fw_ready);
		if (drvpriv.drv_registered)
			padapter->surprise_removed = true;
		unregister_netdev(pnetdev); /* will call netdev_close() */
		flush_scheduled_work();
		udelay(1);
		/* Stop driver mlme relation timer */
		r8712_stop_drv_timers(padapter);
		r871x_dev_unload(padapter);
		r8712_free_drv_sw(padapter);

		/* decrease the reference count of the usb device structure
		 * when disconnect
		 */
		usb_put_dev(udev);
	}
	/* If we didn't unplug usb dongle and remove/insert module, driver
	 * fails on sitesurvey for the first time when device is up.
	 * Reset usb port for sitesurvey fail issue.
	 */
	if (udev->state != USB_STATE_NOTATTACHED)
		usb_reset_device(udev);
}
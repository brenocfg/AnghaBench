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
struct usb_device {int /*<<< orphan*/  dev; } ;
struct firmware {int dummy; } ;
struct TYPE_2__ {struct usb_device* pusbdev; } ;
struct _adapter {int /*<<< orphan*/  pnetdev; struct firmware const* fw; struct usb_interface* pusb_intf; TYPE_1__ dvobjpriv; int /*<<< orphan*/  rtl8712_fw_ready; } ;

/* Variables and functions */
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  register_netdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_put_dev (struct usb_device*) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rtl871x_load_fw_cb(const struct firmware *firmware, void *context)
{
	struct _adapter *adapter = context;

	complete(&adapter->rtl8712_fw_ready);
	if (!firmware) {
		struct usb_device *udev = adapter->dvobjpriv.pusbdev;
		struct usb_interface *usb_intf = adapter->pusb_intf;

		dev_err(&udev->dev, "r8712u: Firmware request failed\n");
		usb_put_dev(udev);
		usb_set_intfdata(usb_intf, NULL);
		return;
	}
	adapter->fw = firmware;
	/* firmware available - start netdev */
	register_netdev(adapter->pnetdev);
}
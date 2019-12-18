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
struct usb_device {int /*<<< orphan*/  dev; } ;
struct p54u_priv {int /*<<< orphan*/  fw_wait_load; struct firmware const* fw; struct usb_interface* intf; struct usb_device* udev; } ;
struct firmware {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  p54u_driver ; 
 int p54u_start_ops (struct p54u_priv*) ; 
 int /*<<< orphan*/  usb_driver_release_interface (int /*<<< orphan*/ *,struct usb_interface*) ; 
 int /*<<< orphan*/  usb_lock_device (struct usb_device*) ; 
 int /*<<< orphan*/  usb_put_intf (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_unlock_device (struct usb_device*) ; 

__attribute__((used)) static void p54u_load_firmware_cb(const struct firmware *firmware,
				  void *context)
{
	struct p54u_priv *priv = context;
	struct usb_device *udev = priv->udev;
	struct usb_interface *intf = priv->intf;
	int err;

	if (firmware) {
		priv->fw = firmware;
		err = p54u_start_ops(priv);
	} else {
		err = -ENOENT;
		dev_err(&udev->dev, "Firmware not found.\n");
	}

	complete(&priv->fw_wait_load);
	/*
	 * At this point p54u_disconnect may have already freed
	 * the "priv" context. Do not use it anymore!
	 */
	priv = NULL;

	if (err) {
		dev_err(&intf->dev, "failed to initialize device (%d)\n", err);

		usb_lock_device(udev);
		usb_driver_release_interface(&p54u_driver, intf);
		usb_unlock_device(udev);
	}

	usb_put_intf(intf);
}
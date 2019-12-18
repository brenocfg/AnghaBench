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
struct usb_device {scalar_t__ state; int /*<<< orphan*/  dev; } ;
struct hif_device_usb {int flags; int /*<<< orphan*/  htc_handle; int /*<<< orphan*/  fw_done; } ;

/* Variables and functions */
 int HIF_USB_READY ; 
 scalar_t__ USB_STATE_NOTATTACHED ; 
 int /*<<< orphan*/  ath9k_hif_usb_dev_deinit (struct hif_device_usb*) ; 
 int /*<<< orphan*/  ath9k_hif_usb_reboot (struct usb_device*) ; 
 int /*<<< orphan*/  ath9k_htc_hw_deinit (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ath9k_htc_hw_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 struct usb_device* interface_to_usbdev (struct usb_interface*) ; 
 int /*<<< orphan*/  kfree (struct hif_device_usb*) ; 
 struct hif_device_usb* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_put_dev (struct usb_device*) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ath9k_hif_usb_disconnect(struct usb_interface *interface)
{
	struct usb_device *udev = interface_to_usbdev(interface);
	struct hif_device_usb *hif_dev = usb_get_intfdata(interface);
	bool unplugged = (udev->state == USB_STATE_NOTATTACHED) ? true : false;

	if (!hif_dev)
		return;

	wait_for_completion(&hif_dev->fw_done);

	if (hif_dev->flags & HIF_USB_READY) {
		ath9k_htc_hw_deinit(hif_dev->htc_handle, unplugged);
		ath9k_htc_hw_free(hif_dev->htc_handle);
		ath9k_hif_usb_dev_deinit(hif_dev);
	}

	usb_set_intfdata(interface, NULL);

	/* If firmware was loaded we should drop it
	 * go back to first stage bootloader. */
	if (!unplugged && (hif_dev->flags & HIF_USB_READY))
		ath9k_hif_usb_reboot(udev);

	kfree(hif_dev);
	dev_info(&udev->dev, "ath9k_htc: USB layer deinitialized\n");
	usb_put_dev(udev);
}
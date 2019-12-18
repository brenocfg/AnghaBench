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
struct brcmf_usbdev_info {int /*<<< orphan*/  dev_init_done; } ;

/* Variables and functions */
 int /*<<< orphan*/  USB ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  brcmf_usb_disconnect_cb (struct brcmf_usbdev_info*) ; 
 int /*<<< orphan*/  kfree (struct brcmf_usbdev_info*) ; 
 scalar_t__ usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
brcmf_usb_disconnect(struct usb_interface *intf)
{
	struct brcmf_usbdev_info *devinfo;

	brcmf_dbg(USB, "Enter\n");
	devinfo = (struct brcmf_usbdev_info *)usb_get_intfdata(intf);

	if (devinfo) {
		wait_for_completion(&devinfo->dev_init_done);
		/* Make sure that devinfo still exists. Firmware probe routines
		 * may have released the device and cleared the intfdata.
		 */
		if (!usb_get_intfdata(intf))
			goto done;

		brcmf_usb_disconnect_cb(devinfo);
		kfree(devinfo);
	}
done:
	brcmf_dbg(USB, "Exit\n");
}
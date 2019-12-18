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
struct usbhid_device {int /*<<< orphan*/  lock; int /*<<< orphan*/  iofl; } ;
struct usb_interface {struct usb_host_interface* cur_altsetting; } ;
struct TYPE_2__ {int /*<<< orphan*/  bInterfaceNumber; } ;
struct usb_host_interface {TYPE_1__ desc; } ;
struct usb_device {int dummy; } ;
struct hid_device {int /*<<< orphan*/  dev_rsize; int /*<<< orphan*/  dev_rdesc; struct usbhid_device* driver_data; } ;

/* Variables and functions */
 int ENOMEM ; 
 int EPERM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HID_CLEAR_HALT ; 
 int /*<<< orphan*/  HID_DT_REPORT ; 
 int /*<<< orphan*/  HID_RESET_PENDING ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dbg_hid (char*) ; 
 int hid_get_class_descriptor (struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hid_restart_io (struct hid_device*) ; 
 int /*<<< orphan*/  hid_set_idle (struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct usb_device* interface_to_usbdev (struct usb_interface*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int memcmp (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 struct hid_device* usb_get_intfdata (struct usb_interface*) ; 

__attribute__((used)) static int hid_post_reset(struct usb_interface *intf)
{
	struct usb_device *dev = interface_to_usbdev (intf);
	struct hid_device *hid = usb_get_intfdata(intf);
	struct usbhid_device *usbhid = hid->driver_data;
	struct usb_host_interface *interface = intf->cur_altsetting;
	int status;
	char *rdesc;

	/* Fetch and examine the HID report descriptor. If this
	 * has changed, then rebind. Since usbcore's check of the
	 * configuration descriptors passed, we already know that
	 * the size of the HID report descriptor has not changed.
	 */
	rdesc = kmalloc(hid->dev_rsize, GFP_KERNEL);
	if (!rdesc)
		return -ENOMEM;

	status = hid_get_class_descriptor(dev,
				interface->desc.bInterfaceNumber,
				HID_DT_REPORT, rdesc, hid->dev_rsize);
	if (status < 0) {
		dbg_hid("reading report descriptor failed (post_reset)\n");
		kfree(rdesc);
		return status;
	}
	status = memcmp(rdesc, hid->dev_rdesc, hid->dev_rsize);
	kfree(rdesc);
	if (status != 0) {
		dbg_hid("report descriptor changed\n");
		return -EPERM;
	}

	/* No need to do another reset or clear a halted endpoint */
	spin_lock_irq(&usbhid->lock);
	clear_bit(HID_RESET_PENDING, &usbhid->iofl);
	clear_bit(HID_CLEAR_HALT, &usbhid->iofl);
	spin_unlock_irq(&usbhid->lock);
	hid_set_idle(dev, intf->cur_altsetting->desc.bInterfaceNumber, 0, 0);

	hid_restart_io(hid);

	return 0;
}
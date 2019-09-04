#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct usb_interface {TYPE_3__* cur_altsetting; } ;
struct roccat_common2_device {int /*<<< orphan*/  chrdev_minor; scalar_t__ roccat_claimed; } ;
struct TYPE_4__ {int /*<<< orphan*/  parent; } ;
struct hid_device {TYPE_1__ dev; } ;
struct TYPE_5__ {scalar_t__ bInterfaceProtocol; } ;
struct TYPE_6__ {TYPE_2__ desc; } ;

/* Variables and functions */
 scalar_t__ RYOS_USB_INTERFACE_PROTOCOL ; 
 struct roccat_common2_device* hid_get_drvdata (struct hid_device*) ; 
 int /*<<< orphan*/  kfree (struct roccat_common2_device*) ; 
 int /*<<< orphan*/  roccat_disconnect (int /*<<< orphan*/ ) ; 
 struct usb_interface* to_usb_interface (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ryos_remove_specials(struct hid_device *hdev)
{
	struct usb_interface *intf = to_usb_interface(hdev->dev.parent);
	struct roccat_common2_device *ryos;

	if (intf->cur_altsetting->desc.bInterfaceProtocol
			!= RYOS_USB_INTERFACE_PROTOCOL)
		return;

	ryos = hid_get_drvdata(hdev);
	if (ryos->roccat_claimed)
		roccat_disconnect(ryos->chrdev_minor);
	kfree(ryos);
}
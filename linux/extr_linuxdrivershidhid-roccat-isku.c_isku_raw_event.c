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
typedef  int /*<<< orphan*/  u8 ;
struct usb_interface {TYPE_3__* cur_altsetting; } ;
struct isku_device {scalar_t__ roccat_claimed; } ;
struct hid_report {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  parent; } ;
struct hid_device {TYPE_1__ dev; } ;
struct TYPE_5__ {scalar_t__ bInterfaceProtocol; } ;
struct TYPE_6__ {TYPE_2__ desc; } ;

/* Variables and functions */
 scalar_t__ ISKU_USB_INTERFACE_PROTOCOL ; 
 struct isku_device* hid_get_drvdata (struct hid_device*) ; 
 int /*<<< orphan*/  isku_keep_values_up_to_date (struct isku_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  isku_report_to_chrdev (struct isku_device*,int /*<<< orphan*/ *) ; 
 struct usb_interface* to_usb_interface (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int isku_raw_event(struct hid_device *hdev,
		struct hid_report *report, u8 *data, int size)
{
	struct usb_interface *intf = to_usb_interface(hdev->dev.parent);
	struct isku_device *isku = hid_get_drvdata(hdev);

	if (intf->cur_altsetting->desc.bInterfaceProtocol
			!= ISKU_USB_INTERFACE_PROTOCOL)
		return 0;

	if (isku == NULL)
		return 0;

	isku_keep_values_up_to_date(isku, data);

	if (isku->roccat_claimed)
		isku_report_to_chrdev(isku, data);

	return 0;
}
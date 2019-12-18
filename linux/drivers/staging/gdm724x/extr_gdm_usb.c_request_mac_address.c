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
typedef  int /*<<< orphan*/  u8 ;
struct usb_device {int dummy; } ;
struct lte_udev {int request_mac_addr; int /*<<< orphan*/  gdm_ed; struct usb_device* usbdev; } ;
struct hci_packet {int /*<<< orphan*/ * data; void* len; void* cmd_evt; } ;

/* Variables and functions */
 int LTE_GET_INFORMATION ; 
 int /*<<< orphan*/  MAC_ADDRESS ; 
 void* gdm_cpu_to_dev16 (int /*<<< orphan*/ ,int) ; 
 int usb_bulk_msg (struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int*,int) ; 
 int /*<<< orphan*/  usb_sndbulkpipe (struct usb_device*,int) ; 

__attribute__((used)) static int request_mac_address(struct lte_udev *udev)
{
	u8 buf[16] = {0,};
	struct hci_packet *hci = (struct hci_packet *)buf;
	struct usb_device *usbdev = udev->usbdev;
	int actual;
	int ret = -1;

	hci->cmd_evt = gdm_cpu_to_dev16(udev->gdm_ed, LTE_GET_INFORMATION);
	hci->len = gdm_cpu_to_dev16(udev->gdm_ed, 1);
	hci->data[0] = MAC_ADDRESS;

	ret = usb_bulk_msg(usbdev, usb_sndbulkpipe(usbdev, 2), buf, 5,
			   &actual, 1000);

	udev->request_mac_addr = 1;

	return ret;
}
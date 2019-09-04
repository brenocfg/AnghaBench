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
struct urb {int transfer_flags; } ;
struct hci_dev {int /*<<< orphan*/  name; } ;
struct btusb_data {int /*<<< orphan*/  isoc_anchor; TYPE_1__* isoc_rx_ep; int /*<<< orphan*/  udev; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_2__ {int /*<<< orphan*/  wMaxPacketSize; int /*<<< orphan*/  bInterval; int /*<<< orphan*/  bEndpointAddress; } ;

/* Variables and functions */
 int BTUSB_MAX_ISOC_FRAMES ; 
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ) ; 
 int ENODEV ; 
 int ENOMEM ; 
 int EPERM ; 
 int URB_FREE_BUFFER ; 
 int URB_ISO_ASAP ; 
 int /*<<< orphan*/  __fill_isoc_descriptor (struct urb*,int,int) ; 
 int /*<<< orphan*/  bt_dev_err (struct hci_dev*,char*,struct urb*,int) ; 
 int /*<<< orphan*/  btusb_isoc_complete ; 
 struct btusb_data* hci_get_drvdata (struct hci_dev*) ; 
 unsigned char* kmalloc (int,int /*<<< orphan*/ ) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 struct urb* usb_alloc_urb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_anchor_urb (struct urb*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_fill_int_urb (struct urb*,int /*<<< orphan*/ ,unsigned int,unsigned char*,int,int /*<<< orphan*/ ,struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_free_urb (struct urb*) ; 
 unsigned int usb_rcvisocpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int usb_submit_urb (struct urb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_unanchor_urb (struct urb*) ; 

__attribute__((used)) static int btusb_submit_isoc_urb(struct hci_dev *hdev, gfp_t mem_flags)
{
	struct btusb_data *data = hci_get_drvdata(hdev);
	struct urb *urb;
	unsigned char *buf;
	unsigned int pipe;
	int err, size;

	BT_DBG("%s", hdev->name);

	if (!data->isoc_rx_ep)
		return -ENODEV;

	urb = usb_alloc_urb(BTUSB_MAX_ISOC_FRAMES, mem_flags);
	if (!urb)
		return -ENOMEM;

	size = le16_to_cpu(data->isoc_rx_ep->wMaxPacketSize) *
						BTUSB_MAX_ISOC_FRAMES;

	buf = kmalloc(size, mem_flags);
	if (!buf) {
		usb_free_urb(urb);
		return -ENOMEM;
	}

	pipe = usb_rcvisocpipe(data->udev, data->isoc_rx_ep->bEndpointAddress);

	usb_fill_int_urb(urb, data->udev, pipe, buf, size, btusb_isoc_complete,
			 hdev, data->isoc_rx_ep->bInterval);

	urb->transfer_flags = URB_FREE_BUFFER | URB_ISO_ASAP;

	__fill_isoc_descriptor(urb, size,
			       le16_to_cpu(data->isoc_rx_ep->wMaxPacketSize));

	usb_anchor_urb(urb, &data->isoc_anchor);

	err = usb_submit_urb(urb, mem_flags);
	if (err < 0) {
		if (err != -EPERM && err != -ENODEV)
			bt_dev_err(hdev, "urb %p submission failed (%d)",
				   urb, -err);
		usb_unanchor_urb(urb);
	}

	usb_free_urb(urb);

	return err;
}
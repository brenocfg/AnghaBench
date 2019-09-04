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
struct urb {int /*<<< orphan*/  transfer_flags; } ;
struct hci_dev {int /*<<< orphan*/  name; } ;
struct bpa10x_data {int /*<<< orphan*/  rx_anchor; int /*<<< orphan*/  udev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  URB_FREE_BUFFER ; 
 int /*<<< orphan*/  bpa10x_rx_complete ; 
 int /*<<< orphan*/  bt_dev_err (struct hci_dev*,char*,struct urb*,int) ; 
 struct bpa10x_data* hci_get_drvdata (struct hci_dev*) ; 
 unsigned char* kmalloc (int,int /*<<< orphan*/ ) ; 
 struct urb* usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_anchor_urb (struct urb*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_fill_bulk_urb (struct urb*,int /*<<< orphan*/ ,unsigned int,unsigned char*,int,int /*<<< orphan*/ ,struct hci_dev*) ; 
 int /*<<< orphan*/  usb_free_urb (struct urb*) ; 
 unsigned int usb_rcvbulkpipe (int /*<<< orphan*/ ,int) ; 
 int usb_submit_urb (struct urb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_unanchor_urb (struct urb*) ; 

__attribute__((used)) static inline int bpa10x_submit_bulk_urb(struct hci_dev *hdev)
{
	struct bpa10x_data *data = hci_get_drvdata(hdev);
	struct urb *urb;
	unsigned char *buf;
	unsigned int pipe;
	int err, size = 64;

	BT_DBG("%s", hdev->name);

	urb = usb_alloc_urb(0, GFP_KERNEL);
	if (!urb)
		return -ENOMEM;

	buf = kmalloc(size, GFP_KERNEL);
	if (!buf) {
		usb_free_urb(urb);
		return -ENOMEM;
	}

	pipe = usb_rcvbulkpipe(data->udev, 0x82);

	usb_fill_bulk_urb(urb, data->udev, pipe,
					buf, size, bpa10x_rx_complete, hdev);

	urb->transfer_flags |= URB_FREE_BUFFER;

	usb_anchor_urb(urb, &data->rx_anchor);

	err = usb_submit_urb(urb, GFP_KERNEL);
	if (err < 0) {
		bt_dev_err(hdev, "urb %p submission failed (%d)", urb, -err);
		usb_unanchor_urb(urb);
	}

	usb_free_urb(urb);

	return err;
}
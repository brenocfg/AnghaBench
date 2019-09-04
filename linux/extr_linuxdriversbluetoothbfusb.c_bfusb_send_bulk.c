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
struct urb {int dummy; } ;
struct sk_buff {int /*<<< orphan*/  len; int /*<<< orphan*/  data; scalar_t__ cb; } ;
struct bfusb_data_scb {struct urb* urb; } ;
struct bfusb_data {int /*<<< orphan*/  pending_tx; int /*<<< orphan*/  pending_q; TYPE_1__* hdev; int /*<<< orphan*/  udev; int /*<<< orphan*/  bulk_out_ep; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct bfusb_data*,struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BT_ERR (char*,int /*<<< orphan*/ ,struct urb*,int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 struct urb* bfusb_get_completed (struct bfusb_data*) ; 
 int /*<<< orphan*/  bfusb_tx_complete ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  skb_unlink (struct sk_buff*,int /*<<< orphan*/ *) ; 
 struct urb* usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_fill_bulk_urb (struct urb*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  usb_free_urb (struct urb*) ; 
 int usb_sndbulkpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int usb_submit_urb (struct urb*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bfusb_send_bulk(struct bfusb_data *data, struct sk_buff *skb)
{
	struct bfusb_data_scb *scb = (void *) skb->cb;
	struct urb *urb = bfusb_get_completed(data);
	int err, pipe;

	BT_DBG("bfusb %p skb %p len %d", data, skb, skb->len);

	if (!urb) {
		urb = usb_alloc_urb(0, GFP_ATOMIC);
		if (!urb)
			return -ENOMEM;
	}

	pipe = usb_sndbulkpipe(data->udev, data->bulk_out_ep);

	usb_fill_bulk_urb(urb, data->udev, pipe, skb->data, skb->len,
			bfusb_tx_complete, skb);

	scb->urb = urb;

	skb_queue_tail(&data->pending_q, skb);

	err = usb_submit_urb(urb, GFP_ATOMIC);
	if (err) {
		BT_ERR("%s bulk tx submit failed urb %p err %d", 
					data->hdev->name, urb, err);
		skb_unlink(skb, &data->pending_q);
		usb_free_urb(urb);
	} else
		atomic_inc(&data->pending_tx);

	return err;
}
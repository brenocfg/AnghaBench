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
struct urb {int /*<<< orphan*/  actual_length; int /*<<< orphan*/  transfer_buffer; int /*<<< orphan*/  pipe; int /*<<< orphan*/  status; struct hci_dev* context; } ;
struct TYPE_2__ {int /*<<< orphan*/  err_rx; } ;
struct hci_dev {TYPE_1__ stat; int /*<<< orphan*/  flags; int /*<<< orphan*/  name; } ;
struct bpa10x_data {int /*<<< orphan*/  rx_anchor; int /*<<< orphan*/ ** rx_skb; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ,struct urb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  HCI_RUNNING ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bpa10x_recv_pkts ; 
 int /*<<< orphan*/  bt_dev_err (struct hci_dev*,char*,...) ; 
 int /*<<< orphan*/ * h4_recv_buf (struct hci_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct bpa10x_data* hci_get_drvdata (struct hci_dev*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_anchor_urb (struct urb*,int /*<<< orphan*/ *) ; 
 int usb_pipebulk (int /*<<< orphan*/ ) ; 
 int usb_submit_urb (struct urb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_unanchor_urb (struct urb*) ; 

__attribute__((used)) static void bpa10x_rx_complete(struct urb *urb)
{
	struct hci_dev *hdev = urb->context;
	struct bpa10x_data *data = hci_get_drvdata(hdev);
	int err;

	BT_DBG("%s urb %p status %d count %d", hdev->name,
					urb, urb->status, urb->actual_length);

	if (!test_bit(HCI_RUNNING, &hdev->flags))
		return;

	if (urb->status == 0) {
		bool idx = usb_pipebulk(urb->pipe);

		data->rx_skb[idx] = h4_recv_buf(hdev, data->rx_skb[idx],
						urb->transfer_buffer,
						urb->actual_length,
						bpa10x_recv_pkts,
						ARRAY_SIZE(bpa10x_recv_pkts));
		if (IS_ERR(data->rx_skb[idx])) {
			bt_dev_err(hdev, "corrupted event packet");
			hdev->stat.err_rx++;
			data->rx_skb[idx] = NULL;
		}
	}

	usb_anchor_urb(urb, &data->rx_anchor);

	err = usb_submit_urb(urb, GFP_ATOMIC);
	if (err < 0) {
		bt_dev_err(hdev, "urb %p failed to resubmit (%d)", urb, -err);
		usb_unanchor_urb(urb);
	}
}
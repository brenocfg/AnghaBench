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
struct sk_buff {scalar_t__ data; } ;
struct TYPE_2__ {int /*<<< orphan*/  sco_tx; int /*<<< orphan*/  acl_tx; int /*<<< orphan*/  cmd_tx; } ;
struct hci_dev {TYPE_1__ stat; int /*<<< orphan*/  name; } ;
struct hci_command_hdr {int /*<<< orphan*/  opcode; } ;
struct btusb_data {int /*<<< orphan*/  flags; } ;
typedef  int __u16 ;

/* Variables and functions */
 int /*<<< orphan*/  BTUSB_BOOTLOADER ; 
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ) ; 
 int EILSEQ ; 
 int ENODEV ; 
#define  HCI_ACLDATA_PKT 130 
#define  HCI_COMMAND_PKT 129 
#define  HCI_SCODATA_PKT 128 
 int /*<<< orphan*/  IS_ERR (struct urb*) ; 
 int PTR_ERR (struct urb*) ; 
 int /*<<< orphan*/  SCO_LINK ; 
 struct urb* alloc_bulk_urb (struct hci_dev*,struct sk_buff*) ; 
 struct urb* alloc_ctrl_urb (struct hci_dev*,struct sk_buff*) ; 
 struct urb* alloc_isoc_urb (struct hci_dev*,struct sk_buff*) ; 
 int hci_conn_num (struct hci_dev*,int /*<<< orphan*/ ) ; 
 struct btusb_data* hci_get_drvdata (struct hci_dev*) ; 
 int hci_skb_pkt_type (struct sk_buff*) ; 
 int /*<<< orphan*/  inject_cmd_complete (struct hci_dev*,int) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int submit_or_queue_tx_urb (struct hci_dev*,struct urb*) ; 
 int submit_tx_urb (struct hci_dev*,struct urb*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int btusb_send_frame_intel(struct hci_dev *hdev, struct sk_buff *skb)
{
	struct btusb_data *data = hci_get_drvdata(hdev);
	struct urb *urb;

	BT_DBG("%s", hdev->name);

	switch (hci_skb_pkt_type(skb)) {
	case HCI_COMMAND_PKT:
		if (test_bit(BTUSB_BOOTLOADER, &data->flags)) {
			struct hci_command_hdr *cmd = (void *)skb->data;
			__u16 opcode = le16_to_cpu(cmd->opcode);

			/* When in bootloader mode and the command 0xfc09
			 * is received, it needs to be send down the
			 * bulk endpoint. So allocate a bulk URB instead.
			 */
			if (opcode == 0xfc09)
				urb = alloc_bulk_urb(hdev, skb);
			else
				urb = alloc_ctrl_urb(hdev, skb);

			/* When the 0xfc01 command is issued to boot into
			 * the operational firmware, it will actually not
			 * send a command complete event. To keep the flow
			 * control working inject that event here.
			 */
			if (opcode == 0xfc01)
				inject_cmd_complete(hdev, opcode);
		} else {
			urb = alloc_ctrl_urb(hdev, skb);
		}
		if (IS_ERR(urb))
			return PTR_ERR(urb);

		hdev->stat.cmd_tx++;
		return submit_or_queue_tx_urb(hdev, urb);

	case HCI_ACLDATA_PKT:
		urb = alloc_bulk_urb(hdev, skb);
		if (IS_ERR(urb))
			return PTR_ERR(urb);

		hdev->stat.acl_tx++;
		return submit_or_queue_tx_urb(hdev, urb);

	case HCI_SCODATA_PKT:
		if (hci_conn_num(hdev, SCO_LINK) < 1)
			return -ENODEV;

		urb = alloc_isoc_urb(hdev, skb);
		if (IS_ERR(urb))
			return PTR_ERR(urb);

		hdev->stat.sco_tx++;
		return submit_tx_urb(hdev, urb);
	}

	return -EILSEQ;
}
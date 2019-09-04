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
typedef  int u16 ;
struct sk_buff {scalar_t__ data; } ;
struct mrvl_data {int id; int rev; int /*<<< orphan*/  flags; } ;
struct hci_uart {struct mrvl_data* priv; } ;
struct hci_mrvl_pkt {int lhs; int rhs; } ;
struct hci_dev {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MRVL_ACK ; 
 int /*<<< orphan*/  MRVL_NAK ; 
 int /*<<< orphan*/  STATE_CHIP_VER_PENDING ; 
 int /*<<< orphan*/  bt_dev_err (struct hci_dev*,char*) ; 
 int /*<<< orphan*/  bt_dev_info (struct hci_dev*,char*,int,int) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct hci_uart* hci_get_drvdata (struct hci_dev*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int le16_to_cpu (int) ; 
 int /*<<< orphan*/  mrvl_send_ack (struct hci_uart*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_mb__after_atomic () ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_bit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mrvl_recv_chip_ver(struct hci_dev *hdev, struct sk_buff *skb)
{
	struct hci_mrvl_pkt *pkt = (void *)skb->data;
	struct hci_uart *hu = hci_get_drvdata(hdev);
	struct mrvl_data *mrvl = hu->priv;
	u16 version = le16_to_cpu(pkt->lhs);
	int ret = 0;

	if ((pkt->lhs ^ pkt->rhs) != 0xffff) {
		bt_dev_err(hdev, "Corrupted mrvl header");
		mrvl_send_ack(hu, MRVL_NAK);
		ret = -EINVAL;
		goto done;
	}
	mrvl_send_ack(hu, MRVL_ACK);

	if (!test_bit(STATE_CHIP_VER_PENDING, &mrvl->flags)) {
		bt_dev_err(hdev, "Received unexpected chip version");
		goto done;
	}

	mrvl->id = version;
	mrvl->rev = version >> 8;

	bt_dev_info(hdev, "Controller id = %x, rev = %x", mrvl->id, mrvl->rev);

	clear_bit(STATE_CHIP_VER_PENDING, &mrvl->flags);
	smp_mb__after_atomic();
	wake_up_bit(&mrvl->flags, STATE_CHIP_VER_PENDING);

done:
	kfree_skb(skb);
	return ret;
}
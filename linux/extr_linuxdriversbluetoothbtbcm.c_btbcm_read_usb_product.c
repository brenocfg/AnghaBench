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
struct sk_buff {int len; } ;
struct hci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 struct sk_buff* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HCI_INIT_TIMEOUT ; 
 scalar_t__ IS_ERR (struct sk_buff*) ; 
 int /*<<< orphan*/  PTR_ERR (struct sk_buff*) ; 
 struct sk_buff* __hci_cmd_sync (struct hci_dev*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bt_dev_err (struct hci_dev*,char*,...) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 

__attribute__((used)) static struct sk_buff *btbcm_read_usb_product(struct hci_dev *hdev)
{
	struct sk_buff *skb;

	skb = __hci_cmd_sync(hdev, 0xfc5a, 0, NULL, HCI_INIT_TIMEOUT);
	if (IS_ERR(skb)) {
		bt_dev_err(hdev, "BCM: Read USB product info failed (%ld)",
			   PTR_ERR(skb));
		return skb;
	}

	if (skb->len != 5) {
		bt_dev_err(hdev, "BCM: USB product length mismatch");
		kfree_skb(skb);
		return ERR_PTR(-EIO);
	}

	return skb;
}
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
struct sk_buff {char** data; } ;
struct hci_dev {int /*<<< orphan*/  quirks; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCI_QUIRK_STRICT_DUPLICATE_FILTER ; 
 int /*<<< orphan*/  IS_ERR (struct sk_buff*) ; 
 int /*<<< orphan*/  bt_dev_info (struct hci_dev*,char*,char*,...) ; 
 struct sk_buff* btbcm_read_controller_features (struct hci_dev*) ; 
 struct sk_buff* btbcm_read_local_name (struct hci_dev*) ; 
 struct sk_buff* btbcm_read_usb_product (struct hci_dev*) ; 
 struct sk_buff* btbcm_read_verbose_config (struct hci_dev*) ; 
 int btbcm_reset (struct hci_dev*) ; 
 int /*<<< orphan*/  get_unaligned_le16 (char**) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int btbcm_setup_apple(struct hci_dev *hdev)
{
	struct sk_buff *skb;
	int err;

	/* Reset */
	err = btbcm_reset(hdev);
	if (err)
		return err;

	/* Read Verbose Config Version Info */
	skb = btbcm_read_verbose_config(hdev);
	if (!IS_ERR(skb)) {
		bt_dev_info(hdev, "BCM: chip id %u build %4.4u",
			    skb->data[1], get_unaligned_le16(skb->data + 5));
		kfree_skb(skb);
	}

	/* Read USB Product Info */
	skb = btbcm_read_usb_product(hdev);
	if (!IS_ERR(skb)) {
		bt_dev_info(hdev, "BCM: product %4.4x:%4.4x",
			    get_unaligned_le16(skb->data + 1),
			    get_unaligned_le16(skb->data + 3));
		kfree_skb(skb);
	}

	/* Read Controller Features */
	skb = btbcm_read_controller_features(hdev);
	if (!IS_ERR(skb)) {
		bt_dev_info(hdev, "BCM: features 0x%2.2x", skb->data[1]);
		kfree_skb(skb);
	}

	/* Read Local Name */
	skb = btbcm_read_local_name(hdev);
	if (!IS_ERR(skb)) {
		bt_dev_info(hdev, "%s", (char *)(skb->data + 1));
		kfree_skb(skb);
	}

	set_bit(HCI_QUIRK_STRICT_DUPLICATE_FILTER, &hdev->quirks);

	return 0;
}
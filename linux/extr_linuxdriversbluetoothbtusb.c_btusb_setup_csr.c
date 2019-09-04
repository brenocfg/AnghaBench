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
struct sk_buff {int len; scalar_t__ data; } ;
struct hci_rp_read_local_version {int /*<<< orphan*/  lmp_subver; int /*<<< orphan*/  manufacturer; } ;
struct hci_dev {int /*<<< orphan*/  quirks; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ) ; 
 int EIO ; 
 int /*<<< orphan*/  HCI_INIT_TIMEOUT ; 
 int /*<<< orphan*/  HCI_OP_READ_LOCAL_VERSION ; 
 int /*<<< orphan*/  HCI_QUIRK_BROKEN_STORED_LINK_KEY ; 
 int /*<<< orphan*/  HCI_QUIRK_RESET_ON_CLOSE ; 
 scalar_t__ IS_ERR (struct sk_buff*) ; 
 int PTR_ERR (struct sk_buff*) ; 
 struct sk_buff* __hci_cmd_sync (struct hci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bt_dev_err (struct hci_dev*,char*,...) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int btusb_setup_csr(struct hci_dev *hdev)
{
	struct hci_rp_read_local_version *rp;
	struct sk_buff *skb;

	BT_DBG("%s", hdev->name);

	skb = __hci_cmd_sync(hdev, HCI_OP_READ_LOCAL_VERSION, 0, NULL,
			     HCI_INIT_TIMEOUT);
	if (IS_ERR(skb)) {
		int err = PTR_ERR(skb);
		bt_dev_err(hdev, "CSR: Local version failed (%d)", err);
		return err;
	}

	if (skb->len != sizeof(struct hci_rp_read_local_version)) {
		bt_dev_err(hdev, "CSR: Local version length mismatch");
		kfree_skb(skb);
		return -EIO;
	}

	rp = (struct hci_rp_read_local_version *)skb->data;

	/* Detect controllers which aren't real CSR ones. */
	if (le16_to_cpu(rp->manufacturer) != 10 ||
	    le16_to_cpu(rp->lmp_subver) == 0x0c5c) {
		/* Clear the reset quirk since this is not an actual
		 * early Bluetooth 1.1 device from CSR.
		 */
		clear_bit(HCI_QUIRK_RESET_ON_CLOSE, &hdev->quirks);

		/* These fake CSR controllers have all a broken
		 * stored link key handling and so just disable it.
		 */
		set_bit(HCI_QUIRK_BROKEN_STORED_LINK_KEY, &hdev->quirks);
	}

	kfree_skb(skb);

	return 0;
}
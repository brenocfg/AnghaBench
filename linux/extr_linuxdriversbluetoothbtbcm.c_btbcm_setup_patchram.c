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
struct sk_buff {scalar_t__ data; } ;
struct hci_dev {int /*<<< orphan*/  quirks; int /*<<< orphan*/  dev; } ;
struct firmware {int dummy; } ;
typedef  int /*<<< orphan*/  fw_name ;

/* Variables and functions */
 int /*<<< orphan*/  HCI_QUIRK_STRICT_DUPLICATE_FILTER ; 
 scalar_t__ IS_ERR (struct sk_buff*) ; 
 int PTR_ERR (struct sk_buff*) ; 
 int /*<<< orphan*/  bt_dev_info (struct hci_dev*,char*,char*) ; 
 int /*<<< orphan*/  btbcm_check_bdaddr (struct hci_dev*) ; 
 int btbcm_initialize (struct hci_dev*,char*,int,int) ; 
 int /*<<< orphan*/  btbcm_patchram (struct hci_dev*,struct firmware const*) ; 
 struct sk_buff* btbcm_read_local_name (struct hci_dev*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int request_firmware (struct firmware const**,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int btbcm_setup_patchram(struct hci_dev *hdev)
{
	char fw_name[64];
	const struct firmware *fw;
	struct sk_buff *skb;
	int err;

	/* Initialize */
	err = btbcm_initialize(hdev, fw_name, sizeof(fw_name), false);
	if (err)
		return err;

	err = request_firmware(&fw, fw_name, &hdev->dev);
	if (err < 0) {
		bt_dev_info(hdev, "BCM: Patch %s not found", fw_name);
		goto done;
	}

	btbcm_patchram(hdev, fw);

	release_firmware(fw);

	/* Re-initialize */
	err = btbcm_initialize(hdev, fw_name, sizeof(fw_name), true);
	if (err)
		return err;

	/* Read Local Name */
	skb = btbcm_read_local_name(hdev);
	if (IS_ERR(skb))
		return PTR_ERR(skb);

	bt_dev_info(hdev, "%s", (char *)(skb->data + 1));
	kfree_skb(skb);

done:
	btbcm_check_bdaddr(hdev);

	set_bit(HCI_QUIRK_STRICT_DUPLICATE_FILTER, &hdev->quirks);

	return 0;
}
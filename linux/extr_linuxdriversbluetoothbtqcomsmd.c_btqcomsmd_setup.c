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
struct sk_buff {int dummy; } ;
struct hci_dev {int /*<<< orphan*/  quirks; } ;
struct btqcomsmd {int /*<<< orphan*/  bdaddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BDADDR_ANY ; 
 int /*<<< orphan*/  HCI_INIT_TIMEOUT ; 
 int /*<<< orphan*/  HCI_OP_RESET ; 
 int /*<<< orphan*/  HCI_QUIRK_INVALID_BDADDR ; 
 scalar_t__ IS_ERR (struct sk_buff*) ; 
 int PTR_ERR (struct sk_buff*) ; 
 struct sk_buff* __hci_cmd_sync (struct hci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bacmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct btqcomsmd* hci_get_drvdata (struct hci_dev*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int qca_set_bdaddr_rome (struct hci_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int btqcomsmd_setup(struct hci_dev *hdev)
{
	struct btqcomsmd *btq = hci_get_drvdata(hdev);
	struct sk_buff *skb;
	int err;

	skb = __hci_cmd_sync(hdev, HCI_OP_RESET, 0, NULL, HCI_INIT_TIMEOUT);
	if (IS_ERR(skb))
		return PTR_ERR(skb);
	kfree_skb(skb);

	/* Devices do not have persistent storage for BD address. If no
	 * BD address has been retrieved during probe, mark the device
	 * as having an invalid BD address.
	 */
	if (!bacmp(&btq->bdaddr, BDADDR_ANY)) {
		set_bit(HCI_QUIRK_INVALID_BDADDR, &hdev->quirks);
		return 0;
	}

	/* When setting a configured BD address fails, mark the device
	 * as having an invalid BD address.
	 */
	err = qca_set_bdaddr_rome(hdev, &btq->bdaddr);
	if (err) {
		set_bit(HCI_QUIRK_INVALID_BDADDR, &hdev->quirks);
		return 0;
	}

	return 0;
}
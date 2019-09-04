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
struct hci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCI_INIT_TIMEOUT ; 
 int HCI_OP_RESET ; 
 scalar_t__ IS_ERR (struct sk_buff*) ; 
 long PTR_ERR (struct sk_buff*) ; 
 struct sk_buff* __hci_cmd_sync (struct hci_dev*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bt_dev_err (struct hci_dev*,char*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 

__attribute__((used)) static int btusb_shutdown_intel(struct hci_dev *hdev)
{
	struct sk_buff *skb;
	long ret;

	/* In the shutdown sequence where Bluetooth is turned off followed
	 * by WiFi being turned off, turning WiFi back on causes issue with
	 * the RF calibration.
	 *
	 * To ensure that any RF activity has been stopped, issue HCI Reset
	 * command to clear all ongoing activity including advertising,
	 * scanning etc.
	 */
	skb = __hci_cmd_sync(hdev, HCI_OP_RESET, 0, NULL, HCI_INIT_TIMEOUT);
	if (IS_ERR(skb)) {
		ret = PTR_ERR(skb);
		bt_dev_err(hdev, "HCI reset during shutdown failed");
		return ret;
	}
	kfree_skb(skb);

	/* Some platforms have an issue with BT LED when the interface is
	 * down or BT radio is turned off, which takes 5 seconds to BT LED
	 * goes off. This command turns off the BT LED immediately.
	 */
	skb = __hci_cmd_sync(hdev, 0xfc3f, 0, NULL, HCI_INIT_TIMEOUT);
	if (IS_ERR(skb)) {
		ret = PTR_ERR(skb);
		bt_dev_err(hdev, "turning off Intel device LED failed");
		return ret;
	}
	kfree_skb(skb);

	return 0;
}
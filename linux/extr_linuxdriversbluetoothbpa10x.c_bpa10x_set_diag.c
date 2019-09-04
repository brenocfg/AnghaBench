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
typedef  int u8 ;
struct sk_buff {int dummy; } ;
struct hci_dev {int /*<<< orphan*/  flags; int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  req ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ) ; 
 int ENETDOWN ; 
 int /*<<< orphan*/  HCI_INIT_TIMEOUT ; 
 int /*<<< orphan*/  HCI_RUNNING ; 
 scalar_t__ IS_ERR (struct sk_buff*) ; 
 int PTR_ERR (struct sk_buff*) ; 
 struct sk_buff* __hci_cmd_sync (struct hci_dev*,int,int,int const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bpa10x_set_diag(struct hci_dev *hdev, bool enable)
{
	const u8 req[] = { 0x00, enable };
	struct sk_buff *skb;

	BT_DBG("%s", hdev->name);

	if (!test_bit(HCI_RUNNING, &hdev->flags))
		return -ENETDOWN;

	/* Enable sniffer operation */
	skb = __hci_cmd_sync(hdev, 0xfc0e, sizeof(req), req, HCI_INIT_TIMEOUT);
	if (IS_ERR(skb))
		return PTR_ERR(skb);

	kfree_skb(skb);
	return 0;
}
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
struct hci_uart {struct bcm_data* priv; } ;
struct hci_dev {int /*<<< orphan*/  flags; } ;
struct bcm_data {int /*<<< orphan*/  txq; } ;

/* Variables and functions */
 int BCM_LM_DIAG_PKT ; 
 int ENETDOWN ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HCI_RUNNING ; 
 struct sk_buff* bt_skb_alloc (int,int /*<<< orphan*/ ) ; 
 struct hci_uart* hci_get_drvdata (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_uart_tx_wakeup (struct hci_uart*) ; 
 int /*<<< orphan*/  skb_put_u8 (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bcm_set_diag(struct hci_dev *hdev, bool enable)
{
	struct hci_uart *hu = hci_get_drvdata(hdev);
	struct bcm_data *bcm = hu->priv;
	struct sk_buff *skb;

	if (!test_bit(HCI_RUNNING, &hdev->flags))
		return -ENETDOWN;

	skb = bt_skb_alloc(3, GFP_KERNEL);
	if (!skb)
		return -ENOMEM;

	skb_put_u8(skb, BCM_LM_DIAG_PKT);
	skb_put_u8(skb, 0xf0);
	skb_put_u8(skb, enable);

	skb_queue_tail(&bcm->txq, skb);
	hci_uart_tx_wakeup(hu);

	return 0;
}
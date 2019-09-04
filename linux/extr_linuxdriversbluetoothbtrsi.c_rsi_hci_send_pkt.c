#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct rsi_hci_adapter {int /*<<< orphan*/  priv; TYPE_1__* proto_ops; } ;
struct TYPE_5__ {int /*<<< orphan*/  sco_tx; int /*<<< orphan*/  acl_tx; int /*<<< orphan*/  cmd_tx; } ;
struct hci_dev {TYPE_2__ stat; } ;
struct TYPE_6__ {int pkt_type; } ;
struct TYPE_4__ {int (* coex_send_pkt ) (int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int ENOMEM ; 
#define  HCI_ACLDATA_PKT 130 
#define  HCI_COMMAND_PKT 129 
#define  HCI_SCODATA_PKT 128 
 int /*<<< orphan*/  RSI_BT_Q ; 
 scalar_t__ RSI_HEADROOM_FOR_BT_HAL ; 
 TYPE_3__* bt_cb (struct sk_buff*) ; 
 struct rsi_hci_adapter* hci_get_drvdata (struct hci_dev*) ; 
 int hci_skb_pkt_type (struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 scalar_t__ skb_headroom (struct sk_buff*) ; 
 struct sk_buff* skb_realloc_headroom (struct sk_buff*,scalar_t__) ; 
 int stub1 (int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int rsi_hci_send_pkt(struct hci_dev *hdev, struct sk_buff *skb)
{
	struct rsi_hci_adapter *h_adapter = hci_get_drvdata(hdev);
	struct sk_buff *new_skb = NULL;

	switch (hci_skb_pkt_type(skb)) {
	case HCI_COMMAND_PKT:
		hdev->stat.cmd_tx++;
		break;
	case HCI_ACLDATA_PKT:
		hdev->stat.acl_tx++;
		break;
	case HCI_SCODATA_PKT:
		hdev->stat.sco_tx++;
		break;
	}

	if (skb_headroom(skb) < RSI_HEADROOM_FOR_BT_HAL) {
		/* Insufficient skb headroom - allocate a new skb */
		new_skb = skb_realloc_headroom(skb, RSI_HEADROOM_FOR_BT_HAL);
		if (unlikely(!new_skb))
			return -ENOMEM;
		bt_cb(new_skb)->pkt_type = hci_skb_pkt_type(skb);
		kfree_skb(skb);
		skb = new_skb;
	}

	return h_adapter->proto_ops->coex_send_pkt(h_adapter->priv, skb,
						   RSI_BT_Q);
}
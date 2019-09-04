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
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {int dummy; } ;
struct qca_data {int /*<<< orphan*/  txq; } ;
struct hci_uart {struct qca_data* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct hci_uart*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BT_ERR (char*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 struct sk_buff* bt_skb_alloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_put_u8 (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 

__attribute__((used)) static int send_hci_ibs_cmd(u8 cmd, struct hci_uart *hu)
{
	int err = 0;
	struct sk_buff *skb = NULL;
	struct qca_data *qca = hu->priv;

	BT_DBG("hu %p send hci ibs cmd 0x%x", hu, cmd);

	skb = bt_skb_alloc(1, GFP_ATOMIC);
	if (!skb) {
		BT_ERR("Failed to allocate memory for HCI_IBS packet");
		return -ENOMEM;
	}

	/* Assign HCI_IBS type */
	skb_put_u8(skb, cmd);

	skb_queue_tail(&qca->txq, skb);

	return err;
}
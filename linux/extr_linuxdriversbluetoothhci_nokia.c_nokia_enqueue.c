#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int len; } ;
struct nokia_bt_dev {int /*<<< orphan*/  txq; } ;
struct hci_uart {struct nokia_bt_dev* priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  pkt_type; } ;

/* Variables and functions */
 TYPE_1__* bt_cb (struct sk_buff*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int skb_pad (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_push (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_put_u8 (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 

__attribute__((used)) static int nokia_enqueue(struct hci_uart *hu, struct sk_buff *skb)
{
	struct nokia_bt_dev *btdev = hu->priv;
	int err;

	/* Prepend skb with frame type */
	memcpy(skb_push(skb, 1), &bt_cb(skb)->pkt_type, 1);

	/* Packets must be word aligned */
	if (skb->len % 2) {
		err = skb_pad(skb, 1);
		if (err)
			return err;
		skb_put_u8(skb, 0x00);
	}

	skb_queue_tail(&btdev->txq, skb);

	return 0;
}
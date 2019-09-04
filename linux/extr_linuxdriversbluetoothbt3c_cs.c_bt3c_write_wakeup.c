#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int len; int /*<<< orphan*/  data; } ;
struct bt3c_info {TYPE_3__* hdev; int /*<<< orphan*/  tx_state; int /*<<< orphan*/  txq; TYPE_4__* p_dev; } ;
struct TYPE_8__ {TYPE_1__** resource; } ;
struct TYPE_6__ {int byte_tx; } ;
struct TYPE_7__ {TYPE_2__ stat; } ;
struct TYPE_5__ {unsigned int start; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_ERR (char*) ; 
 int /*<<< orphan*/  XMIT_SENDING ; 
 int bt3c_write (unsigned int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  pcmcia_dev_present (TYPE_4__*) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bt3c_write_wakeup(struct bt3c_info *info)
{
	if (!info) {
		BT_ERR("Unknown device");
		return;
	}

	if (test_and_set_bit(XMIT_SENDING, &(info->tx_state)))
		return;

	do {
		unsigned int iobase = info->p_dev->resource[0]->start;
		register struct sk_buff *skb;
		int len;

		if (!pcmcia_dev_present(info->p_dev))
			break;

		skb = skb_dequeue(&(info->txq));
		if (!skb) {
			clear_bit(XMIT_SENDING, &(info->tx_state));
			break;
		}

		/* Send frame */
		len = bt3c_write(iobase, 256, skb->data, skb->len);

		if (len != skb->len)
			BT_ERR("Very strange");

		kfree_skb(skb);

		info->hdev->stat.byte_tx += len;

	} while (0);
}
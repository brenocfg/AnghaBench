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
typedef  unsigned int u32 ;
struct sk_buff {int dummy; } ;
struct rtl8169_private {scalar_t__ TxDescArray; struct ring_info* tx_skb; } ;
struct ring_info {unsigned int len; struct sk_buff* skb; } ;

/* Variables and functions */
 unsigned int NUM_TX_DESC ; 
 int /*<<< orphan*/  dev_consume_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  rtl8169_unmap_tx_skb (int /*<<< orphan*/ ,struct ring_info*,scalar_t__) ; 
 int /*<<< orphan*/  tp_to_dev (struct rtl8169_private*) ; 

__attribute__((used)) static void rtl8169_tx_clear_range(struct rtl8169_private *tp, u32 start,
				   unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++) {
		unsigned int entry = (start + i) % NUM_TX_DESC;
		struct ring_info *tx_skb = tp->tx_skb + entry;
		unsigned int len = tx_skb->len;

		if (len) {
			struct sk_buff *skb = tx_skb->skb;

			rtl8169_unmap_tx_skb(tp_to_dev(tp), tx_skb,
					     tp->TxDescArray + entry);
			if (skb) {
				dev_consume_skb_any(skb);
				tx_skb->skb = NULL;
			}
		}
	}
}
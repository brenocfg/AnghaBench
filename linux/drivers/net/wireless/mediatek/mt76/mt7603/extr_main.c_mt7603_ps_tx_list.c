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
struct sk_buff_head {int dummy; } ;
struct sk_buff {int dummy; } ;
struct mt7603_dev {int dummy; } ;

/* Variables and functions */
 struct sk_buff* __skb_dequeue (struct sk_buff_head*) ; 
 int /*<<< orphan*/  mt76_tx_queue_skb_raw (struct mt7603_dev*,int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_get_queue_mapping (struct sk_buff*) ; 

__attribute__((used)) static void
mt7603_ps_tx_list(struct mt7603_dev *dev, struct sk_buff_head *list)
{
	struct sk_buff *skb;

	while ((skb = __skb_dequeue(list)) != NULL)
		mt76_tx_queue_skb_raw(dev, skb_get_queue_mapping(skb),
				      skb, 0);
}
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
struct sk_buff_head {int dummy; } ;
struct sk_buff {int dummy; } ;
struct TYPE_2__ {struct sk_buff_head event_queue; } ;
struct qtnf_bus {TYPE_1__ trans; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 struct sk_buff* skb_dequeue (struct sk_buff_head*) ; 

__attribute__((used)) static void qtnf_trans_free_events(struct qtnf_bus *bus)
{
	struct sk_buff_head *event_queue = &bus->trans.event_queue;
	struct sk_buff *current_event_skb = skb_dequeue(event_queue);

	while (current_event_skb) {
		dev_kfree_skb_any(current_event_skb);
		current_event_skb = skb_dequeue(event_queue);
	}
}
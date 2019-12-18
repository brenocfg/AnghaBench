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
typedef  unsigned int u16 ;
struct sk_buff {int dummy; } ;
struct net_device {unsigned int real_num_tx_queues; } ;

/* Variables and functions */
 unsigned int skb_get_hash (struct sk_buff*) ; 

__attribute__((used)) static u16 xennet_select_queue(struct net_device *dev, struct sk_buff *skb,
			       struct net_device *sb_dev)
{
	unsigned int num_queues = dev->real_num_tx_queues;
	u32 hash;
	u16 queue_idx;

	/* First, check if there is only one queue */
	if (num_queues == 1) {
		queue_idx = 0;
	} else {
		hash = skb_get_hash(skb);
		queue_idx = hash % num_queues;
	}

	return queue_idx;
}
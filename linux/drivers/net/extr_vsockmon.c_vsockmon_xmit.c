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
struct sk_buff {int len; } ;
struct pcpu_lstats {int bytes; int /*<<< orphan*/  syncp; int /*<<< orphan*/  packets; } ;
struct net_device {int /*<<< orphan*/  lstats; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;

/* Variables and functions */
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 struct pcpu_lstats* this_cpu_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  u64_stats_update_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  u64_stats_update_end (int /*<<< orphan*/ *) ; 

__attribute__((used)) static netdev_tx_t vsockmon_xmit(struct sk_buff *skb, struct net_device *dev)
{
	int len = skb->len;
	struct pcpu_lstats *stats = this_cpu_ptr(dev->lstats);

	u64_stats_update_begin(&stats->syncp);
	stats->bytes += len;
	stats->packets++;
	u64_stats_update_end(&stats->syncp);

	dev_kfree_skb(skb);

	return NETDEV_TX_OK;
}
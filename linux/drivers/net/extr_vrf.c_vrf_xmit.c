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
struct pcpu_dstats {int tx_bytes; int /*<<< orphan*/  syncp; int /*<<< orphan*/  tx_pkts; } ;
struct net_device {TYPE_1__* dstats; } ;
typedef  scalar_t__ netdev_tx_t ;
struct TYPE_2__ {int /*<<< orphan*/  tx_drps; } ;

/* Variables and functions */
 scalar_t__ NET_XMIT_CN ; 
 scalar_t__ NET_XMIT_SUCCESS ; 
 scalar_t__ is_ip_tx_frame (struct sk_buff*,struct net_device*) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  this_cpu_inc (int /*<<< orphan*/ ) ; 
 struct pcpu_dstats* this_cpu_ptr (TYPE_1__*) ; 
 int /*<<< orphan*/  u64_stats_update_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  u64_stats_update_end (int /*<<< orphan*/ *) ; 

__attribute__((used)) static netdev_tx_t vrf_xmit(struct sk_buff *skb, struct net_device *dev)
{
	int len = skb->len;
	netdev_tx_t ret = is_ip_tx_frame(skb, dev);

	if (likely(ret == NET_XMIT_SUCCESS || ret == NET_XMIT_CN)) {
		struct pcpu_dstats *dstats = this_cpu_ptr(dev->dstats);

		u64_stats_update_begin(&dstats->syncp);
		dstats->tx_pkts++;
		dstats->tx_bytes += len;
		u64_stats_update_end(&dstats->syncp);
	} else {
		this_cpu_inc(dev->dstats->tx_drps);
	}

	return ret;
}
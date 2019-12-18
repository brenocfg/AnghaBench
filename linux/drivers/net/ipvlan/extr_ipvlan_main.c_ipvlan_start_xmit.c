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
struct net_device {int dummy; } ;
struct ipvl_pcpu_stats {int tx_bytes; int /*<<< orphan*/  syncp; int /*<<< orphan*/  tx_pkts; } ;
struct ipvl_dev {TYPE_1__* pcpu_stats; } ;
typedef  int netdev_tx_t ;
struct TYPE_2__ {int /*<<< orphan*/  tx_drps; } ;

/* Variables and functions */
 int NET_XMIT_CN ; 
 int NET_XMIT_SUCCESS ; 
 int ipvlan_queue_xmit (struct sk_buff*,struct net_device*) ; 
 scalar_t__ likely (int) ; 
 struct ipvl_dev* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  this_cpu_inc (int /*<<< orphan*/ ) ; 
 struct ipvl_pcpu_stats* this_cpu_ptr (TYPE_1__*) ; 
 int /*<<< orphan*/  u64_stats_update_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  u64_stats_update_end (int /*<<< orphan*/ *) ; 

__attribute__((used)) static netdev_tx_t ipvlan_start_xmit(struct sk_buff *skb,
				     struct net_device *dev)
{
	const struct ipvl_dev *ipvlan = netdev_priv(dev);
	int skblen = skb->len;
	int ret;

	ret = ipvlan_queue_xmit(skb, dev);
	if (likely(ret == NET_XMIT_SUCCESS || ret == NET_XMIT_CN)) {
		struct ipvl_pcpu_stats *pcptr;

		pcptr = this_cpu_ptr(ipvlan->pcpu_stats);

		u64_stats_update_begin(&pcptr->syncp);
		pcptr->tx_pkts++;
		pcptr->tx_bytes += skblen;
		u64_stats_update_end(&pcptr->syncp);
	} else {
		this_cpu_inc(ipvlan->pcpu_stats->tx_drps);
	}
	return ret;
}
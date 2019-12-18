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
struct nfp_repr_pcpu_stats {unsigned int tx_bytes; int /*<<< orphan*/  syncp; int /*<<< orphan*/  tx_packets; } ;
struct nfp_repr {TYPE_1__* stats; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  tx_drops; } ;

/* Variables and functions */
 int NET_XMIT_CN ; 
 int NET_XMIT_SUCCESS ; 
 struct nfp_repr* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  this_cpu_inc (int /*<<< orphan*/ ) ; 
 struct nfp_repr_pcpu_stats* this_cpu_ptr (TYPE_1__*) ; 
 int /*<<< orphan*/  u64_stats_update_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  u64_stats_update_end (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void
nfp_repr_inc_tx_stats(struct net_device *netdev, unsigned int len,
		      int tx_status)
{
	struct nfp_repr *repr = netdev_priv(netdev);
	struct nfp_repr_pcpu_stats *stats;

	if (unlikely(tx_status != NET_XMIT_SUCCESS &&
		     tx_status != NET_XMIT_CN)) {
		this_cpu_inc(repr->stats->tx_drops);
		return;
	}

	stats = this_cpu_ptr(repr->stats);
	u64_stats_update_begin(&stats->syncp);
	stats->tx_packets++;
	stats->tx_bytes += len;
	u64_stats_update_end(&stats->syncp);
}
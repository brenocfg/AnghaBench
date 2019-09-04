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
struct nfp_repr_pcpu_stats {unsigned int rx_bytes; int /*<<< orphan*/  syncp; int /*<<< orphan*/  rx_packets; } ;
struct nfp_repr {int /*<<< orphan*/  stats; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 struct nfp_repr* netdev_priv (struct net_device*) ; 
 struct nfp_repr_pcpu_stats* this_cpu_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  u64_stats_update_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  u64_stats_update_end (int /*<<< orphan*/ *) ; 

void nfp_repr_inc_rx_stats(struct net_device *netdev, unsigned int len)
{
	struct nfp_repr *repr = netdev_priv(netdev);
	struct nfp_repr_pcpu_stats *stats;

	stats = this_cpu_ptr(repr->stats);
	u64_stats_update_begin(&stats->syncp);
	stats->rx_packets++;
	stats->rx_bytes += len;
	u64_stats_update_end(&stats->syncp);
}
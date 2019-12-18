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
struct pcpu_dstats {int rx_bytes; int /*<<< orphan*/  syncp; int /*<<< orphan*/  rx_pkts; } ;
struct net_device {int /*<<< orphan*/  dstats; } ;

/* Variables and functions */
 struct pcpu_dstats* this_cpu_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  u64_stats_update_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  u64_stats_update_end (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void vrf_rx_stats(struct net_device *dev, int len)
{
	struct pcpu_dstats *dstats = this_cpu_ptr(dev->dstats);

	u64_stats_update_begin(&dstats->syncp);
	dstats->rx_pkts++;
	dstats->rx_bytes += len;
	u64_stats_update_end(&dstats->syncp);
}
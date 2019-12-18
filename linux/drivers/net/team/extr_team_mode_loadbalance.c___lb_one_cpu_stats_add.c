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
struct u64_stats_sync {int dummy; } ;
struct lb_stats {scalar_t__ tx_bytes; } ;

/* Variables and functions */
 unsigned int u64_stats_fetch_begin_irq (struct u64_stats_sync*) ; 
 scalar_t__ u64_stats_fetch_retry_irq (struct u64_stats_sync*,unsigned int) ; 

__attribute__((used)) static void __lb_one_cpu_stats_add(struct lb_stats *acc_stats,
				   struct lb_stats *cpu_stats,
				   struct u64_stats_sync *syncp)
{
	unsigned int start;
	struct lb_stats tmp;

	do {
		start = u64_stats_fetch_begin_irq(syncp);
		tmp.tx_bytes = cpu_stats->tx_bytes;
	} while (u64_stats_fetch_retry_irq(syncp, start));
	acc_stats->tx_bytes += tmp.tx_bytes;
}
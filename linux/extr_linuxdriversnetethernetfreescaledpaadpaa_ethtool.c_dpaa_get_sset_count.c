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
struct net_device {int dummy; } ;

/* Variables and functions */
 unsigned int DPAA_BPS_NUM ; 
 unsigned int DPAA_STATS_GLOBAL_LEN ; 
 unsigned int DPAA_STATS_PERCPU_LEN ; 
 int EOPNOTSUPP ; 
#define  ETH_SS_STATS 128 
 int num_online_cpus () ; 

__attribute__((used)) static int dpaa_get_sset_count(struct net_device *net_dev, int type)
{
	unsigned int total_stats, num_stats;

	num_stats   = num_online_cpus() + 1;
	total_stats = num_stats * (DPAA_STATS_PERCPU_LEN + DPAA_BPS_NUM) +
			DPAA_STATS_GLOBAL_LEN;

	switch (type) {
	case ETH_SS_STATS:
		return total_stats;
	default:
		return -EOPNOTSUPP;
	}
}
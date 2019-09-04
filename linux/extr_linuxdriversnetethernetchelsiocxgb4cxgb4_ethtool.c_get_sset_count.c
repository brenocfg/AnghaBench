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
 int ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int EOPNOTSUPP ; 
#define  ETH_SS_PRIV_FLAGS 129 
#define  ETH_SS_STATS 128 
 int /*<<< orphan*/  adapter_stats_strings ; 
 int /*<<< orphan*/  cxgb4_priv_flags_strings ; 
 int /*<<< orphan*/  loopback_stats_strings ; 
 int /*<<< orphan*/  stats_strings ; 

__attribute__((used)) static int get_sset_count(struct net_device *dev, int sset)
{
	switch (sset) {
	case ETH_SS_STATS:
		return ARRAY_SIZE(stats_strings) +
		       ARRAY_SIZE(adapter_stats_strings) +
		       ARRAY_SIZE(loopback_stats_strings);
	case ETH_SS_PRIV_FLAGS:
		return ARRAY_SIZE(cxgb4_priv_flags_strings);
	default:
		return -EOPNOTSUPP;
	}
}
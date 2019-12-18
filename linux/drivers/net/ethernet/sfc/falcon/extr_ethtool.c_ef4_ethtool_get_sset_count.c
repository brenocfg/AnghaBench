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
struct net_device {int dummy; } ;
struct ef4_nic {TYPE_1__* type; } ;
struct TYPE_2__ {int (* describe_stats ) (struct ef4_nic*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int EF4_ETHTOOL_SW_STAT_COUNT ; 
 int EINVAL ; 
#define  ETH_SS_STATS 129 
#define  ETH_SS_TEST 128 
 int ef4_describe_per_queue_stats (struct ef4_nic*,int /*<<< orphan*/ *) ; 
 int ef4_ethtool_fill_self_tests (struct ef4_nic*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct ef4_nic* netdev_priv (struct net_device*) ; 
 int stub1 (struct ef4_nic*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ef4_ethtool_get_sset_count(struct net_device *net_dev,
				      int string_set)
{
	struct ef4_nic *efx = netdev_priv(net_dev);

	switch (string_set) {
	case ETH_SS_STATS:
		return efx->type->describe_stats(efx, NULL) +
		       EF4_ETHTOOL_SW_STAT_COUNT +
		       ef4_describe_per_queue_stats(efx, NULL);
	case ETH_SS_TEST:
		return ef4_ethtool_fill_self_tests(efx, NULL, NULL, NULL);
	default:
		return -EINVAL;
	}
}
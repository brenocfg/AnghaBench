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
struct efx_nic {TYPE_1__* type; } ;
struct TYPE_2__ {int (* describe_stats ) (struct efx_nic*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int EFX_ETHTOOL_SW_STAT_COUNT ; 
 int EINVAL ; 
#define  ETH_SS_STATS 129 
#define  ETH_SS_TEST 128 
 int efx_describe_per_queue_stats (struct efx_nic*,int /*<<< orphan*/ *) ; 
 int efx_ethtool_fill_self_tests (struct efx_nic*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int efx_ptp_describe_stats (struct efx_nic*,int /*<<< orphan*/ *) ; 
 struct efx_nic* netdev_priv (struct net_device*) ; 
 int stub1 (struct efx_nic*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int efx_ethtool_get_sset_count(struct net_device *net_dev,
				      int string_set)
{
	struct efx_nic *efx = netdev_priv(net_dev);

	switch (string_set) {
	case ETH_SS_STATS:
		return efx->type->describe_stats(efx, NULL) +
		       EFX_ETHTOOL_SW_STAT_COUNT +
		       efx_describe_per_queue_stats(efx, NULL) +
		       efx_ptp_describe_stats(efx, NULL);
	case ETH_SS_TEST:
		return efx_ethtool_fill_self_tests(efx, NULL, NULL, NULL);
	default:
		return -EINVAL;
	}
}
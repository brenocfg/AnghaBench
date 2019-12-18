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
struct qlcnic_adapter {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  ETH_SS_STATS 129 
#define  ETH_SS_TEST 128 
 int QLCNIC_TEST_LEN ; 
 struct qlcnic_adapter* netdev_priv (struct net_device*) ; 
 int qlcnic_dev_statistics_len (struct qlcnic_adapter*) ; 

__attribute__((used)) static int qlcnic_get_sset_count(struct net_device *dev, int sset)
{

	struct qlcnic_adapter *adapter = netdev_priv(dev);
	switch (sset) {
	case ETH_SS_TEST:
		return QLCNIC_TEST_LEN;
	case ETH_SS_STATS:
		return qlcnic_dev_statistics_len(adapter);
	default:
		return -EOPNOTSUPP;
	}
}
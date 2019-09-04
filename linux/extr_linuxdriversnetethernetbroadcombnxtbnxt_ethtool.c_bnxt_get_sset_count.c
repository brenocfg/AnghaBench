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
struct bnxt {int num_tests; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  ETH_SS_STATS 129 
#define  ETH_SS_TEST 128 
 int bnxt_get_num_stats (struct bnxt*) ; 
 struct bnxt* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int bnxt_get_sset_count(struct net_device *dev, int sset)
{
	struct bnxt *bp = netdev_priv(dev);

	switch (sset) {
	case ETH_SS_STATS:
		return bnxt_get_num_stats(bp);
	case ETH_SS_TEST:
		if (!bp->num_tests)
			return -EOPNOTSUPP;
		return bp->num_tests;
	default:
		return -EOPNOTSUPP;
	}
}
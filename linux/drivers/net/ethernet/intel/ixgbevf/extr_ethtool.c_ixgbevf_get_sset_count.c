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
 int EINVAL ; 
#define  ETH_SS_PRIV_FLAGS 130 
#define  ETH_SS_STATS 129 
#define  ETH_SS_TEST 128 
 int IXGBEVF_PRIV_FLAGS_STR_LEN ; 
 int IXGBEVF_STATS_LEN ; 
 int IXGBEVF_TEST_LEN ; 

__attribute__((used)) static int ixgbevf_get_sset_count(struct net_device *netdev, int stringset)
{
	switch (stringset) {
	case ETH_SS_TEST:
		return IXGBEVF_TEST_LEN;
	case ETH_SS_STATS:
		return IXGBEVF_STATS_LEN;
	case ETH_SS_PRIV_FLAGS:
		return IXGBEVF_PRIV_FLAGS_STR_LEN;
	default:
		return -EINVAL;
	}
}
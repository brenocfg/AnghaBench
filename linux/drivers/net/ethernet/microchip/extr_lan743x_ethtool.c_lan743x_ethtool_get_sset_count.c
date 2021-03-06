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
 int /*<<< orphan*/  lan743x_priv_flags_strings ; 
 int /*<<< orphan*/  lan743x_set0_hw_cnt_strings ; 
 int /*<<< orphan*/  lan743x_set1_sw_cnt_strings ; 
 int /*<<< orphan*/  lan743x_set2_hw_cnt_strings ; 

__attribute__((used)) static int lan743x_ethtool_get_sset_count(struct net_device *netdev, int sset)
{
	switch (sset) {
	case ETH_SS_STATS:
	{
		int ret;

		ret = ARRAY_SIZE(lan743x_set0_hw_cnt_strings);
		ret += ARRAY_SIZE(lan743x_set1_sw_cnt_strings);
		ret += ARRAY_SIZE(lan743x_set2_hw_cnt_strings);
		return ret;
	}
	case ETH_SS_PRIV_FLAGS:
		return ARRAY_SIZE(lan743x_priv_flags_strings);
	default:
		return -EOPNOTSUPP;
	}
}
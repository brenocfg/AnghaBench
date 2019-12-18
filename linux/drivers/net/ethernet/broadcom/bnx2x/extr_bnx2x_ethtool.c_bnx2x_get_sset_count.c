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
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int BNX2X_NUM_Q_STATS ; 
 int BNX2X_NUM_STATS ; 
 int BNX2X_NUM_TESTS (struct bnx2x*) ; 
 int BNX2X_PRI_FLAG_LEN ; 
 int EINVAL ; 
#define  ETH_SS_PRIV_FLAGS 130 
#define  ETH_SS_STATS 129 
#define  ETH_SS_TEST 128 
 int /*<<< orphan*/  HIDE_PORT_STAT (struct bnx2x*) ; 
 int /*<<< orphan*/  IS_PORT_STAT (int) ; 
 int bnx2x_num_stat_queues (struct bnx2x*) ; 
 int /*<<< orphan*/  is_multi (struct bnx2x*) ; 
 struct bnx2x* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int bnx2x_get_sset_count(struct net_device *dev, int stringset)
{
	struct bnx2x *bp = netdev_priv(dev);
	int i, num_strings = 0;

	switch (stringset) {
	case ETH_SS_STATS:
		if (is_multi(bp)) {
			num_strings = bnx2x_num_stat_queues(bp) *
				      BNX2X_NUM_Q_STATS;
		} else
			num_strings = 0;
		if (HIDE_PORT_STAT(bp)) {
			for (i = 0; i < BNX2X_NUM_STATS; i++)
				if (!IS_PORT_STAT(i))
					num_strings++;
		} else
			num_strings += BNX2X_NUM_STATS;

		return num_strings;

	case ETH_SS_TEST:
		return BNX2X_NUM_TESTS(bp);

	case ETH_SS_PRIV_FLAGS:
		return BNX2X_PRI_FLAG_LEN;

	default:
		return -EINVAL;
	}
}
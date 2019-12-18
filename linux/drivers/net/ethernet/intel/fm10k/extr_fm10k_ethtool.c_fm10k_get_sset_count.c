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
struct TYPE_2__ {int max_queues; int /*<<< orphan*/  type; } ;
struct fm10k_hw {TYPE_1__ mac; } ;
struct fm10k_intfc {struct fm10k_hw hw; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  ETH_SS_PRIV_FLAGS 130 
#define  ETH_SS_STATS 129 
#define  ETH_SS_TEST 128 
 int FM10K_PF_STATS_LEN ; 
 int FM10K_PRV_FLAG_LEN ; 
 int FM10K_QUEUE_STATS_LEN ; 
 int FM10K_STATIC_STATS_LEN ; 
 int FM10K_TEST_LEN ; 
 int /*<<< orphan*/  fm10k_mac_vf ; 
 struct fm10k_intfc* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int fm10k_get_sset_count(struct net_device *dev, int sset)
{
	struct fm10k_intfc *interface = netdev_priv(dev);
	struct fm10k_hw *hw = &interface->hw;
	int stats_len = FM10K_STATIC_STATS_LEN;

	switch (sset) {
	case ETH_SS_TEST:
		return FM10K_TEST_LEN;
	case ETH_SS_STATS:
		stats_len += hw->mac.max_queues * 2 * FM10K_QUEUE_STATS_LEN;

		if (hw->mac.type != fm10k_mac_vf)
			stats_len += FM10K_PF_STATS_LEN;

		return stats_len;
	case ETH_SS_PRIV_FLAGS:
		return FM10K_PRV_FLAG_LEN;
	default:
		return -EOPNOTSUPP;
	}
}
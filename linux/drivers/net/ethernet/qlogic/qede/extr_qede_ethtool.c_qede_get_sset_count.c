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
struct TYPE_2__ {int num_tc; } ;
struct qede_dev {int /*<<< orphan*/  xdp_prog; TYPE_1__ dev_info; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_VERBOSE (struct qede_dev*,int /*<<< orphan*/ ,char*,int) ; 
 int EINVAL ; 
#define  ETH_SS_PRIV_FLAGS 130 
#define  ETH_SS_STATS 129 
#define  ETH_SS_TEST 128 
 int /*<<< orphan*/  IS_VF (struct qede_dev*) ; 
 int QEDE_ETHTOOL_TEST_MAX ; 
 int QEDE_NUM_RQSTATS ; 
 int QEDE_NUM_STATS ; 
 int QEDE_NUM_TQSTATS ; 
 int QEDE_PRI_FLAG_LEN ; 
 int QEDE_RSS_COUNT (struct qede_dev*) ; 
 int QEDE_TSS_COUNT (struct qede_dev*) ; 
 int /*<<< orphan*/  QED_MSG_DEBUG ; 
 struct qede_dev* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  qede_is_irrelevant_stat (struct qede_dev*,int) ; 

__attribute__((used)) static int qede_get_sset_count(struct net_device *dev, int stringset)
{
	struct qede_dev *edev = netdev_priv(dev);
	int num_stats = QEDE_NUM_STATS, i;

	switch (stringset) {
	case ETH_SS_STATS:
		for (i = 0; i < QEDE_NUM_STATS; i++)
			if (qede_is_irrelevant_stat(edev, i))
				num_stats--;

		/* Account for the Regular Tx statistics */
		num_stats += QEDE_TSS_COUNT(edev) * QEDE_NUM_TQSTATS *
				edev->dev_info.num_tc;

		/* Account for the Regular Rx statistics */
		num_stats += QEDE_RSS_COUNT(edev) * QEDE_NUM_RQSTATS;

		/* Account for XDP statistics [if needed] */
		if (edev->xdp_prog)
			num_stats += QEDE_RSS_COUNT(edev) * QEDE_NUM_TQSTATS;
		return num_stats;

	case ETH_SS_PRIV_FLAGS:
		return QEDE_PRI_FLAG_LEN;
	case ETH_SS_TEST:
		if (!IS_VF(edev))
			return QEDE_ETHTOOL_TEST_MAX;
		else
			return 0;
	default:
		DP_VERBOSE(edev, QED_MSG_DEBUG,
			   "Unsupported stringset 0x%08x\n", stringset);
		return -EINVAL;
	}
}
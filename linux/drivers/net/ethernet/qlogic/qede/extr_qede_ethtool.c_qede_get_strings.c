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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct qede_dev {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_VERBOSE (struct qede_dev*,int /*<<< orphan*/ ,char*,int) ; 
 int ETH_GSTRING_LEN ; 
#define  ETH_SS_PRIV_FLAGS 130 
#define  ETH_SS_STATS 129 
#define  ETH_SS_TEST 128 
 int QEDE_ETHTOOL_TEST_MAX ; 
 int QEDE_PRI_FLAG_LEN ; 
 int /*<<< orphan*/  QED_MSG_DEBUG ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct qede_dev* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  qede_get_strings_stats (struct qede_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qede_private_arr ; 
 int /*<<< orphan*/  qede_tests_str_arr ; 

__attribute__((used)) static void qede_get_strings(struct net_device *dev, u32 stringset, u8 *buf)
{
	struct qede_dev *edev = netdev_priv(dev);

	switch (stringset) {
	case ETH_SS_STATS:
		qede_get_strings_stats(edev, buf);
		break;
	case ETH_SS_PRIV_FLAGS:
		memcpy(buf, qede_private_arr,
		       ETH_GSTRING_LEN * QEDE_PRI_FLAG_LEN);
		break;
	case ETH_SS_TEST:
		memcpy(buf, qede_tests_str_arr,
		       ETH_GSTRING_LEN * QEDE_ETHTOOL_TEST_MAX);
		break;
	default:
		DP_VERBOSE(edev, QED_MSG_DEBUG,
			   "Unsupported stringset 0x%08x\n", stringset);
	}
}
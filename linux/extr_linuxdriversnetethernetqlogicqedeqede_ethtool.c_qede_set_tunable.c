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
typedef  int /*<<< orphan*/  u32 ;
struct qede_dev {int /*<<< orphan*/  rx_copybreak; } ;
struct net_device {int dummy; } ;
struct ethtool_tunable {int id; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_VERBOSE (struct qede_dev*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
#define  ETHTOOL_RX_COPYBREAK 128 
 int /*<<< orphan*/  QEDE_MIN_PKT_LEN ; 
 int /*<<< orphan*/  QEDE_RX_HDR_SIZE ; 
 int /*<<< orphan*/  QED_MSG_DEBUG ; 
 struct qede_dev* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int qede_set_tunable(struct net_device *dev,
			    const struct ethtool_tunable *tuna,
			    const void *data)
{
	struct qede_dev *edev = netdev_priv(dev);
	u32 val;

	switch (tuna->id) {
	case ETHTOOL_RX_COPYBREAK:
		val = *(u32 *)data;
		if (val < QEDE_MIN_PKT_LEN || val > QEDE_RX_HDR_SIZE) {
			DP_VERBOSE(edev, QED_MSG_DEBUG,
				   "Invalid rx copy break value, range is [%u, %u]",
				   QEDE_MIN_PKT_LEN, QEDE_RX_HDR_SIZE);
			return -EINVAL;
		}

		edev->rx_copybreak = *(u32 *)data;
		break;
	default:
		return -EOPNOTSUPP;
	}

	return 0;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_3__ {int num_hwfns; } ;
struct TYPE_4__ {TYPE_1__ common; } ;
struct qede_dev {int fp_num_tx; int fp_num_rx; int req_queues; int req_num_tx; int req_num_rx; int /*<<< orphan*/  rss_ind_table; int /*<<< orphan*/  rss_params_inited; TYPE_2__ dev_info; } ;
struct net_device {int dummy; } ;
struct ethtool_channels {int rx_count; int tx_count; int combined_count; scalar_t__ other_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_VERBOSE (struct qede_dev*,int,char*,...) ; 
 int EINVAL ; 
 int NETIF_MSG_IFDOWN ; 
 int NETIF_MSG_IFUP ; 
 int QEDE_MAX_RSS_CNT (struct qede_dev*) ; 
 int QEDE_QUEUE_CNT (struct qede_dev*) ; 
 scalar_t__ QEDE_RSS_COUNT (struct qede_dev*) ; 
 int /*<<< orphan*/  QEDE_RSS_INDIR_INITED ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct qede_dev* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  qede_reload (struct qede_dev*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int qede_set_channels(struct net_device *dev,
			     struct ethtool_channels *channels)
{
	struct qede_dev *edev = netdev_priv(dev);
	u32 count;

	DP_VERBOSE(edev, (NETIF_MSG_IFUP | NETIF_MSG_IFDOWN),
		   "set-channels command parameters: rx = %d, tx = %d, other = %d, combined = %d\n",
		   channels->rx_count, channels->tx_count,
		   channels->other_count, channels->combined_count);

	count = channels->rx_count + channels->tx_count +
			channels->combined_count;

	/* We don't support `other' channels */
	if (channels->other_count) {
		DP_VERBOSE(edev, (NETIF_MSG_IFUP | NETIF_MSG_IFDOWN),
			   "command parameters not supported\n");
		return -EINVAL;
	}

	if (!(channels->combined_count || (channels->rx_count &&
					   channels->tx_count))) {
		DP_VERBOSE(edev, (NETIF_MSG_IFUP | NETIF_MSG_IFDOWN),
			   "need to request at least one transmit and one receive channel\n");
		return -EINVAL;
	}

	if (count > QEDE_MAX_RSS_CNT(edev)) {
		DP_VERBOSE(edev, (NETIF_MSG_IFUP | NETIF_MSG_IFDOWN),
			   "requested channels = %d max supported channels = %d\n",
			   count, QEDE_MAX_RSS_CNT(edev));
		return -EINVAL;
	}

	/* Check if there was a change in the active parameters */
	if ((count == QEDE_QUEUE_CNT(edev)) &&
	    (channels->tx_count == edev->fp_num_tx) &&
	    (channels->rx_count == edev->fp_num_rx)) {
		DP_VERBOSE(edev, (NETIF_MSG_IFUP | NETIF_MSG_IFDOWN),
			   "No change in active parameters\n");
		return 0;
	}

	/* We need the number of queues to be divisible between the hwfns */
	if ((count % edev->dev_info.common.num_hwfns) ||
	    (channels->tx_count % edev->dev_info.common.num_hwfns) ||
	    (channels->rx_count % edev->dev_info.common.num_hwfns)) {
		DP_VERBOSE(edev, (NETIF_MSG_IFUP | NETIF_MSG_IFDOWN),
			   "Number of channels must be divisible by %04x\n",
			   edev->dev_info.common.num_hwfns);
		return -EINVAL;
	}

	/* Set number of queues and reload if necessary */
	edev->req_queues = count;
	edev->req_num_tx = channels->tx_count;
	edev->req_num_rx = channels->rx_count;
	/* Reset the indirection table if rx queue count is updated */
	if ((edev->req_queues - edev->req_num_tx) != QEDE_RSS_COUNT(edev)) {
		edev->rss_params_inited &= ~QEDE_RSS_INDIR_INITED;
		memset(edev->rss_ind_table, 0, sizeof(edev->rss_ind_table));
	}

	qede_reload(edev, NULL, false);

	return 0;
}
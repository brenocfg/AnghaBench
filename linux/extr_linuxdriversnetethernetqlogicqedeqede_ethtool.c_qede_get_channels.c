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
struct qede_dev {scalar_t__ fp_num_rx; scalar_t__ fp_num_tx; } ;
struct net_device {int dummy; } ;
struct ethtool_channels {scalar_t__ rx_count; scalar_t__ tx_count; scalar_t__ combined_count; void* max_tx; void* max_rx; void* max_combined; } ;

/* Variables and functions */
 void* QEDE_MAX_RSS_CNT (struct qede_dev*) ; 
 scalar_t__ QEDE_QUEUE_CNT (struct qede_dev*) ; 
 struct qede_dev* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void qede_get_channels(struct net_device *dev,
			      struct ethtool_channels *channels)
{
	struct qede_dev *edev = netdev_priv(dev);

	channels->max_combined = QEDE_MAX_RSS_CNT(edev);
	channels->max_rx = QEDE_MAX_RSS_CNT(edev);
	channels->max_tx = QEDE_MAX_RSS_CNT(edev);
	channels->combined_count = QEDE_QUEUE_CNT(edev) - edev->fp_num_tx -
					edev->fp_num_rx;
	channels->tx_count = edev->fp_num_tx;
	channels->rx_count = edev->fp_num_rx;
}
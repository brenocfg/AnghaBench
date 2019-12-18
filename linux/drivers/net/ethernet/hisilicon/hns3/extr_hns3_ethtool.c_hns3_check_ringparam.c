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
struct ethtool_ringparam {scalar_t__ tx_pending; scalar_t__ rx_pending; scalar_t__ rx_jumbo_pending; scalar_t__ rx_mini_pending; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 scalar_t__ HNS3_RING_MAX_PENDING ; 
 scalar_t__ HNS3_RING_MIN_PENDING ; 
 scalar_t__ hns3_nic_resetting (struct net_device*) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int hns3_check_ringparam(struct net_device *ndev,
				struct ethtool_ringparam *param)
{
	if (hns3_nic_resetting(ndev))
		return -EBUSY;

	if (param->rx_mini_pending || param->rx_jumbo_pending)
		return -EINVAL;

	if (param->tx_pending > HNS3_RING_MAX_PENDING ||
	    param->tx_pending < HNS3_RING_MIN_PENDING ||
	    param->rx_pending > HNS3_RING_MAX_PENDING ||
	    param->rx_pending < HNS3_RING_MIN_PENDING) {
		netdev_err(ndev, "Queue depth out of range [%d-%d]\n",
			   HNS3_RING_MIN_PENDING, HNS3_RING_MAX_PENDING);
		return -EINVAL;
	}

	return 0;
}
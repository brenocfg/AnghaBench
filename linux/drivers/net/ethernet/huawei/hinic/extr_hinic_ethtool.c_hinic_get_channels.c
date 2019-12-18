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
struct TYPE_2__ {int /*<<< orphan*/  max_qps; } ;
struct hinic_hwdev {TYPE_1__ nic_cap; } ;
struct hinic_dev {struct hinic_hwdev* hwdev; } ;
struct ethtool_channels {scalar_t__ combined_count; scalar_t__ other_count; void* tx_count; void* rx_count; scalar_t__ max_combined; scalar_t__ max_other; int /*<<< orphan*/  max_tx; int /*<<< orphan*/  max_rx; } ;

/* Variables and functions */
 void* hinic_hwdev_num_qps (struct hinic_hwdev*) ; 
 struct hinic_dev* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void hinic_get_channels(struct net_device *netdev,
			       struct ethtool_channels *channels)
{
	struct hinic_dev *nic_dev = netdev_priv(netdev);
	struct hinic_hwdev *hwdev = nic_dev->hwdev;

	channels->max_rx = hwdev->nic_cap.max_qps;
	channels->max_tx = hwdev->nic_cap.max_qps;
	channels->max_other = 0;
	channels->max_combined = 0;
	channels->rx_count = hinic_hwdev_num_qps(hwdev);
	channels->tx_count = hinic_hwdev_num_qps(hwdev);
	channels->other_count = 0;
	channels->combined_count = 0;
}
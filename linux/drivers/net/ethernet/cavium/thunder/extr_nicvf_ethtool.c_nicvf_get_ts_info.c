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
struct nicvf {int /*<<< orphan*/  ptp_clock; } ;
struct net_device {int dummy; } ;
struct ethtool_ts_info {int so_timestamping; int tx_types; int rx_filters; int /*<<< orphan*/  phc_index; } ;

/* Variables and functions */
 int HWTSTAMP_FILTER_ALL ; 
 int HWTSTAMP_FILTER_NONE ; 
 int HWTSTAMP_TX_OFF ; 
 int HWTSTAMP_TX_ON ; 
 int SOF_TIMESTAMPING_RAW_HARDWARE ; 
 int SOF_TIMESTAMPING_RX_HARDWARE ; 
 int SOF_TIMESTAMPING_RX_SOFTWARE ; 
 int SOF_TIMESTAMPING_SOFTWARE ; 
 int SOF_TIMESTAMPING_TX_HARDWARE ; 
 int SOF_TIMESTAMPING_TX_SOFTWARE ; 
 int /*<<< orphan*/  cavium_ptp_clock_index (int /*<<< orphan*/ ) ; 
 int ethtool_op_get_ts_info (struct net_device*,struct ethtool_ts_info*) ; 
 struct nicvf* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int nicvf_get_ts_info(struct net_device *netdev,
			     struct ethtool_ts_info *info)
{
	struct nicvf *nic = netdev_priv(netdev);

	if (!nic->ptp_clock)
		return ethtool_op_get_ts_info(netdev, info);

	info->so_timestamping = SOF_TIMESTAMPING_TX_SOFTWARE |
				SOF_TIMESTAMPING_RX_SOFTWARE |
				SOF_TIMESTAMPING_SOFTWARE |
				SOF_TIMESTAMPING_TX_HARDWARE |
				SOF_TIMESTAMPING_RX_HARDWARE |
				SOF_TIMESTAMPING_RAW_HARDWARE;

	info->phc_index = cavium_ptp_clock_index(nic->ptp_clock);

	info->tx_types = (1 << HWTSTAMP_TX_OFF) | (1 << HWTSTAMP_TX_ON);

	info->rx_filters = (1 << HWTSTAMP_FILTER_NONE) |
			   (1 << HWTSTAMP_FILTER_ALL);

	return 0;
}
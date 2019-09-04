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
struct fec_enet_private {scalar_t__ ptp_clock; scalar_t__ bufdesc_ex; } ;
struct ethtool_ts_info {int so_timestamping; int phc_index; int tx_types; int rx_filters; } ;

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
 int ethtool_op_get_ts_info (struct net_device*,struct ethtool_ts_info*) ; 
 struct fec_enet_private* netdev_priv (struct net_device*) ; 
 int ptp_clock_index (scalar_t__) ; 

__attribute__((used)) static int fec_enet_get_ts_info(struct net_device *ndev,
				struct ethtool_ts_info *info)
{
	struct fec_enet_private *fep = netdev_priv(ndev);

	if (fep->bufdesc_ex) {

		info->so_timestamping = SOF_TIMESTAMPING_TX_SOFTWARE |
					SOF_TIMESTAMPING_RX_SOFTWARE |
					SOF_TIMESTAMPING_SOFTWARE |
					SOF_TIMESTAMPING_TX_HARDWARE |
					SOF_TIMESTAMPING_RX_HARDWARE |
					SOF_TIMESTAMPING_RAW_HARDWARE;
		if (fep->ptp_clock)
			info->phc_index = ptp_clock_index(fep->ptp_clock);
		else
			info->phc_index = -1;

		info->tx_types = (1 << HWTSTAMP_TX_OFF) |
				 (1 << HWTSTAMP_TX_ON);

		info->rx_filters = (1 << HWTSTAMP_FILTER_NONE) |
				   (1 << HWTSTAMP_FILTER_ALL);
		return 0;
	} else {
		return ethtool_op_get_ts_info(ndev, info);
	}
}
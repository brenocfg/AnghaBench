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
struct port_info {struct adapter* adapter; } ;
struct net_device {int dummy; } ;
struct ethtool_ts_info {int so_timestamping; int tx_types; int rx_filters; int phc_index; } ;
struct adapter {scalar_t__ ptp_clock; } ;

/* Variables and functions */
 int HWTSTAMP_FILTER_NONE ; 
 int HWTSTAMP_FILTER_PTP_V1_L4_DELAY_REQ ; 
 int HWTSTAMP_FILTER_PTP_V1_L4_SYNC ; 
 int HWTSTAMP_FILTER_PTP_V2_L4_DELAY_REQ ; 
 int HWTSTAMP_FILTER_PTP_V2_L4_EVENT ; 
 int HWTSTAMP_FILTER_PTP_V2_L4_SYNC ; 
 int HWTSTAMP_TX_OFF ; 
 int HWTSTAMP_TX_ON ; 
 int SOF_TIMESTAMPING_RAW_HARDWARE ; 
 int SOF_TIMESTAMPING_RX_HARDWARE ; 
 int SOF_TIMESTAMPING_RX_SOFTWARE ; 
 int SOF_TIMESTAMPING_SOFTWARE ; 
 int SOF_TIMESTAMPING_TX_HARDWARE ; 
 int SOF_TIMESTAMPING_TX_SOFTWARE ; 
 struct port_info* netdev_priv (struct net_device*) ; 
 int ptp_clock_index (scalar_t__) ; 

__attribute__((used)) static int get_ts_info(struct net_device *dev, struct ethtool_ts_info *ts_info)
{
	struct port_info *pi = netdev_priv(dev);
	struct  adapter *adapter = pi->adapter;

	ts_info->so_timestamping = SOF_TIMESTAMPING_TX_SOFTWARE |
				   SOF_TIMESTAMPING_RX_SOFTWARE |
				   SOF_TIMESTAMPING_SOFTWARE;

	ts_info->so_timestamping |= SOF_TIMESTAMPING_RX_HARDWARE |
				    SOF_TIMESTAMPING_TX_HARDWARE |
				    SOF_TIMESTAMPING_RAW_HARDWARE;

	ts_info->tx_types = (1 << HWTSTAMP_TX_OFF) |
			    (1 << HWTSTAMP_TX_ON);

	ts_info->rx_filters = (1 << HWTSTAMP_FILTER_NONE) |
			      (1 << HWTSTAMP_FILTER_PTP_V2_L4_EVENT) |
			      (1 << HWTSTAMP_FILTER_PTP_V1_L4_SYNC) |
			      (1 << HWTSTAMP_FILTER_PTP_V1_L4_DELAY_REQ) |
			      (1 << HWTSTAMP_FILTER_PTP_V2_L4_SYNC) |
			      (1 << HWTSTAMP_FILTER_PTP_V2_L4_DELAY_REQ);

	if (adapter->ptp_clock)
		ts_info->phc_index = ptp_clock_index(adapter->ptp_clock);
	else
		ts_info->phc_index = -1;

	return 0;
}
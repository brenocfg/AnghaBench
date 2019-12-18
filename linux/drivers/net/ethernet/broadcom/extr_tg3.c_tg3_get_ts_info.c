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
struct tg3 {scalar_t__ ptp_clock; } ;
struct net_device {int dummy; } ;
struct ethtool_ts_info {int so_timestamping; int phc_index; int tx_types; int rx_filters; } ;

/* Variables and functions */
 int HWTSTAMP_FILTER_NONE ; 
 int HWTSTAMP_FILTER_PTP_V1_L4_EVENT ; 
 int HWTSTAMP_FILTER_PTP_V2_L2_EVENT ; 
 int HWTSTAMP_FILTER_PTP_V2_L4_EVENT ; 
 int HWTSTAMP_TX_OFF ; 
 int HWTSTAMP_TX_ON ; 
 int /*<<< orphan*/  PTP_CAPABLE ; 
 int SOF_TIMESTAMPING_RAW_HARDWARE ; 
 int SOF_TIMESTAMPING_RX_HARDWARE ; 
 int SOF_TIMESTAMPING_RX_SOFTWARE ; 
 int SOF_TIMESTAMPING_SOFTWARE ; 
 int SOF_TIMESTAMPING_TX_HARDWARE ; 
 int SOF_TIMESTAMPING_TX_SOFTWARE ; 
 struct tg3* netdev_priv (struct net_device*) ; 
 int ptp_clock_index (scalar_t__) ; 
 scalar_t__ tg3_flag (struct tg3*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tg3_get_ts_info(struct net_device *dev, struct ethtool_ts_info *info)
{
	struct tg3 *tp = netdev_priv(dev);

	info->so_timestamping = SOF_TIMESTAMPING_TX_SOFTWARE |
				SOF_TIMESTAMPING_RX_SOFTWARE |
				SOF_TIMESTAMPING_SOFTWARE;

	if (tg3_flag(tp, PTP_CAPABLE)) {
		info->so_timestamping |= SOF_TIMESTAMPING_TX_HARDWARE |
					SOF_TIMESTAMPING_RX_HARDWARE |
					SOF_TIMESTAMPING_RAW_HARDWARE;
	}

	if (tp->ptp_clock)
		info->phc_index = ptp_clock_index(tp->ptp_clock);
	else
		info->phc_index = -1;

	info->tx_types = (1 << HWTSTAMP_TX_OFF) | (1 << HWTSTAMP_TX_ON);

	info->rx_filters = (1 << HWTSTAMP_FILTER_NONE) |
			   (1 << HWTSTAMP_FILTER_PTP_V1_L4_EVENT) |
			   (1 << HWTSTAMP_FILTER_PTP_V2_L2_EVENT) |
			   (1 << HWTSTAMP_FILTER_PTP_V2_L4_EVENT);
	return 0;
}
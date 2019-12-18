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
struct ethtool_ts_info {int phc_index; int so_timestamping; int tx_types; int rx_filters; } ;

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
 int /*<<< orphan*/  enetc_phc_index ; 
 int* symbol_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  symbol_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int enetc_get_ts_info(struct net_device *ndev,
			     struct ethtool_ts_info *info)
{
	int *phc_idx;

	phc_idx = symbol_get(enetc_phc_index);
	if (phc_idx) {
		info->phc_index = *phc_idx;
		symbol_put(enetc_phc_index);
	} else {
		info->phc_index = -1;
	}

#ifdef CONFIG_FSL_ENETC_HW_TIMESTAMPING
	info->so_timestamping = SOF_TIMESTAMPING_TX_HARDWARE |
				SOF_TIMESTAMPING_RX_HARDWARE |
				SOF_TIMESTAMPING_RAW_HARDWARE;

	info->tx_types = (1 << HWTSTAMP_TX_OFF) |
			 (1 << HWTSTAMP_TX_ON);
	info->rx_filters = (1 << HWTSTAMP_FILTER_NONE) |
			   (1 << HWTSTAMP_FILTER_ALL);
#else
	info->so_timestamping = SOF_TIMESTAMPING_RX_SOFTWARE |
				SOF_TIMESTAMPING_SOFTWARE;
#endif
	return 0;
}
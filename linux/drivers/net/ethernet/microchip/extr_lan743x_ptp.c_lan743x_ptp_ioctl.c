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
struct lan743x_adapter {int /*<<< orphan*/  netdev; int /*<<< orphan*/ * tx; } ;
struct ifreq {int /*<<< orphan*/  ifr_data; } ;
struct hwtstamp_config {int flags; int tx_type; } ;
typedef  int /*<<< orphan*/  config ;

/* Variables and functions */
 int EFAULT ; 
 int EINVAL ; 
#define  HWTSTAMP_TX_OFF 130 
#define  HWTSTAMP_TX_ON 129 
#define  HWTSTAMP_TX_ONESTEP_SYNC 128 
 int LAN743X_MAX_TX_CHANNELS ; 
 scalar_t__ copy_from_user (struct hwtstamp_config*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ copy_to_user (int /*<<< orphan*/ ,struct hwtstamp_config*,int) ; 
 int /*<<< orphan*/  drv ; 
 int /*<<< orphan*/  lan743x_ptp_set_sync_ts_insert (struct lan743x_adapter*,int) ; 
 int /*<<< orphan*/  lan743x_tx_set_timestamping_mode (int /*<<< orphan*/ *,int,int) ; 
 struct lan743x_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_err (struct lan743x_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  netif_warn (struct lan743x_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 

int lan743x_ptp_ioctl(struct net_device *netdev, struct ifreq *ifr, int cmd)
{
	struct lan743x_adapter *adapter = netdev_priv(netdev);
	struct hwtstamp_config config;
	int ret = 0;
	int index;

	if (!ifr) {
		netif_err(adapter, drv, adapter->netdev,
			  "SIOCSHWTSTAMP, ifr == NULL\n");
		return -EINVAL;
	}

	if (copy_from_user(&config, ifr->ifr_data, sizeof(config)))
		return -EFAULT;

	if (config.flags) {
		netif_warn(adapter, drv, adapter->netdev,
			   "ignoring hwtstamp_config.flags == 0x%08X, expected 0\n",
			   config.flags);
	}

	switch (config.tx_type) {
	case HWTSTAMP_TX_OFF:
		for (index = 0; index < LAN743X_MAX_TX_CHANNELS;
			index++)
			lan743x_tx_set_timestamping_mode(&adapter->tx[index],
							 false, false);
		lan743x_ptp_set_sync_ts_insert(adapter, false);
		break;
	case HWTSTAMP_TX_ON:
		for (index = 0; index < LAN743X_MAX_TX_CHANNELS;
			index++)
			lan743x_tx_set_timestamping_mode(&adapter->tx[index],
							 true, false);
		lan743x_ptp_set_sync_ts_insert(adapter, false);
		break;
	case HWTSTAMP_TX_ONESTEP_SYNC:
		for (index = 0; index < LAN743X_MAX_TX_CHANNELS;
			index++)
			lan743x_tx_set_timestamping_mode(&adapter->tx[index],
							 true, true);

		lan743x_ptp_set_sync_ts_insert(adapter, true);
		break;
	default:
		netif_warn(adapter, drv, adapter->netdev,
			   "  tx_type = %d, UNKNOWN\n", config.tx_type);
		ret = -EINVAL;
		break;
	}

	if (!ret)
		return copy_to_user(ifr->ifr_data, &config,
			sizeof(config)) ? -EFAULT : 0;
	return ret;
}
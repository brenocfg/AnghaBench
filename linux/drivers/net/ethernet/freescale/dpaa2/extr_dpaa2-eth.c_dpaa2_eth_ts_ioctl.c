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
struct ifreq {int /*<<< orphan*/  ifr_data; } ;
struct hwtstamp_config {int tx_type; scalar_t__ rx_filter; } ;
struct dpaa2_eth_priv {int tx_tstamp; int rx_tstamp; } ;
typedef  int /*<<< orphan*/  config ;

/* Variables and functions */
 int EFAULT ; 
 int ERANGE ; 
 scalar_t__ HWTSTAMP_FILTER_ALL ; 
 scalar_t__ HWTSTAMP_FILTER_NONE ; 
#define  HWTSTAMP_TX_OFF 129 
#define  HWTSTAMP_TX_ON 128 
 scalar_t__ copy_from_user (struct hwtstamp_config*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ copy_to_user (int /*<<< orphan*/ ,struct hwtstamp_config*,int) ; 
 struct dpaa2_eth_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int dpaa2_eth_ts_ioctl(struct net_device *dev, struct ifreq *rq, int cmd)
{
	struct dpaa2_eth_priv *priv = netdev_priv(dev);
	struct hwtstamp_config config;

	if (copy_from_user(&config, rq->ifr_data, sizeof(config)))
		return -EFAULT;

	switch (config.tx_type) {
	case HWTSTAMP_TX_OFF:
		priv->tx_tstamp = false;
		break;
	case HWTSTAMP_TX_ON:
		priv->tx_tstamp = true;
		break;
	default:
		return -ERANGE;
	}

	if (config.rx_filter == HWTSTAMP_FILTER_NONE) {
		priv->rx_tstamp = false;
	} else {
		priv->rx_tstamp = true;
		/* TS is set for all frame types, not only those requested */
		config.rx_filter = HWTSTAMP_FILTER_ALL;
	}

	return copy_to_user(rq->ifr_data, &config, sizeof(config)) ?
			-EFAULT : 0;
}
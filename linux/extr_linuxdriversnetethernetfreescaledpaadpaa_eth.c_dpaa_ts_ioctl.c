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
struct ifreq {int /*<<< orphan*/  ifr_data; } ;
struct hwtstamp_config {int tx_type; scalar_t__ rx_filter; } ;
struct dpaa_priv {int tx_tstamp; int rx_tstamp; TYPE_1__* mac_dev; } ;
typedef  int /*<<< orphan*/  config ;
struct TYPE_2__ {int /*<<< orphan*/  fman_mac; int /*<<< orphan*/  (* set_tstamp ) (int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int EFAULT ; 
 int ERANGE ; 
 scalar_t__ HWTSTAMP_FILTER_ALL ; 
 scalar_t__ HWTSTAMP_FILTER_NONE ; 
#define  HWTSTAMP_TX_OFF 129 
#define  HWTSTAMP_TX_ON 128 
 scalar_t__ copy_from_user (struct hwtstamp_config*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ copy_to_user (int /*<<< orphan*/ ,struct hwtstamp_config*,int) ; 
 struct dpaa_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int dpaa_ts_ioctl(struct net_device *dev, struct ifreq *rq, int cmd)
{
	struct dpaa_priv *priv = netdev_priv(dev);
	struct hwtstamp_config config;

	if (copy_from_user(&config, rq->ifr_data, sizeof(config)))
		return -EFAULT;

	switch (config.tx_type) {
	case HWTSTAMP_TX_OFF:
		/* Couldn't disable rx/tx timestamping separately.
		 * Do nothing here.
		 */
		priv->tx_tstamp = false;
		break;
	case HWTSTAMP_TX_ON:
		priv->mac_dev->set_tstamp(priv->mac_dev->fman_mac, true);
		priv->tx_tstamp = true;
		break;
	default:
		return -ERANGE;
	}

	if (config.rx_filter == HWTSTAMP_FILTER_NONE) {
		/* Couldn't disable rx/tx timestamping separately.
		 * Do nothing here.
		 */
		priv->rx_tstamp = false;
	} else {
		priv->mac_dev->set_tstamp(priv->mac_dev->fman_mac, true);
		priv->rx_tstamp = true;
		/* TS is set for all frame types, not only those requested */
		config.rx_filter = HWTSTAMP_FILTER_ALL;
	}

	return copy_to_user(rq->ifr_data, &config, sizeof(config)) ?
			-EFAULT : 0;
}
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
struct xgbe_prv_data {unsigned int rx_desc_count; unsigned int tx_desc_count; } ;
struct net_device {int dummy; } ;
struct ethtool_ringparam {unsigned int rx_pending; unsigned int tx_pending; scalar_t__ rx_jumbo_pending; scalar_t__ rx_mini_pending; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int XGBE_RX_DESC_CNT_MAX ; 
 unsigned int XGBE_RX_DESC_CNT_MIN ; 
 unsigned int XGBE_TX_DESC_CNT_MAX ; 
 unsigned int XGBE_TX_DESC_CNT_MIN ; 
 unsigned int __rounddown_pow_of_two (unsigned int) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,...) ; 
 int /*<<< orphan*/  netdev_notice (struct net_device*,char*,unsigned int) ; 
 struct xgbe_prv_data* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  xgbe_restart_dev (struct xgbe_prv_data*) ; 

__attribute__((used)) static int xgbe_set_ringparam(struct net_device *netdev,
			      struct ethtool_ringparam *ringparam)
{
	struct xgbe_prv_data *pdata = netdev_priv(netdev);
	unsigned int rx, tx;

	if (ringparam->rx_mini_pending || ringparam->rx_jumbo_pending) {
		netdev_err(netdev, "unsupported ring parameter\n");
		return -EINVAL;
	}

	if ((ringparam->rx_pending < XGBE_RX_DESC_CNT_MIN) ||
	    (ringparam->rx_pending > XGBE_RX_DESC_CNT_MAX)) {
		netdev_err(netdev,
			   "rx ring parameter must be between %u and %u\n",
			   XGBE_RX_DESC_CNT_MIN, XGBE_RX_DESC_CNT_MAX);
		return -EINVAL;
	}

	if ((ringparam->tx_pending < XGBE_TX_DESC_CNT_MIN) ||
	    (ringparam->tx_pending > XGBE_TX_DESC_CNT_MAX)) {
		netdev_err(netdev,
			   "tx ring parameter must be between %u and %u\n",
			   XGBE_TX_DESC_CNT_MIN, XGBE_TX_DESC_CNT_MAX);
		return -EINVAL;
	}

	rx = __rounddown_pow_of_two(ringparam->rx_pending);
	if (rx != ringparam->rx_pending)
		netdev_notice(netdev,
			      "rx ring parameter rounded to power of two: %u\n",
			      rx);

	tx = __rounddown_pow_of_two(ringparam->tx_pending);
	if (tx != ringparam->tx_pending)
		netdev_notice(netdev,
			      "tx ring parameter rounded to power of two: %u\n",
			      tx);

	if ((rx == pdata->rx_desc_count) &&
	    (tx == pdata->tx_desc_count))
		goto out;

	pdata->rx_desc_count = rx;
	pdata->tx_desc_count = tx;

	xgbe_restart_dev(pdata);

out:
	return 0;
}
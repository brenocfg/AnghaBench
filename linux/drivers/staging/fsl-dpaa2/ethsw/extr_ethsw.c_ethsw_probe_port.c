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
typedef  size_t u16 ;
struct net_device {int /*<<< orphan*/  max_mtu; int /*<<< orphan*/  min_mtu; int /*<<< orphan*/ * ethtool_ops; int /*<<< orphan*/ * netdev_ops; } ;
struct ethsw_port_priv {size_t idx; int flood; int /*<<< orphan*/  stp_state; struct ethsw_core* ethsw_data; struct net_device* netdev; } ;
struct ethsw_core {struct ethsw_port_priv** ports; struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BR_STATE_FORWARDING ; 
 int ENOMEM ; 
 int /*<<< orphan*/  ETHSW_MAX_FRAME_LENGTH ; 
 int /*<<< orphan*/  ETH_MIN_MTU ; 
 int /*<<< orphan*/  SET_NETDEV_DEV (struct net_device*,struct device*) ; 
 struct net_device* alloc_etherdev (int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  ethsw_port_ethtool_ops ; 
 int ethsw_port_init (struct ethsw_port_priv*,size_t) ; 
 int /*<<< orphan*/  ethsw_port_ops ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 struct ethsw_port_priv* netdev_priv (struct net_device*) ; 
 int register_netdev (struct net_device*) ; 

__attribute__((used)) static int ethsw_probe_port(struct ethsw_core *ethsw, u16 port_idx)
{
	struct ethsw_port_priv *port_priv;
	struct device *dev = ethsw->dev;
	struct net_device *port_netdev;
	int err;

	port_netdev = alloc_etherdev(sizeof(struct ethsw_port_priv));
	if (!port_netdev) {
		dev_err(dev, "alloc_etherdev error\n");
		return -ENOMEM;
	}

	port_priv = netdev_priv(port_netdev);
	port_priv->netdev = port_netdev;
	port_priv->ethsw_data = ethsw;

	port_priv->idx = port_idx;
	port_priv->stp_state = BR_STATE_FORWARDING;

	/* Flooding is implicitly enabled */
	port_priv->flood = true;

	SET_NETDEV_DEV(port_netdev, dev);
	port_netdev->netdev_ops = &ethsw_port_ops;
	port_netdev->ethtool_ops = &ethsw_port_ethtool_ops;

	/* Set MTU limits */
	port_netdev->min_mtu = ETH_MIN_MTU;
	port_netdev->max_mtu = ETHSW_MAX_FRAME_LENGTH;

	err = ethsw_port_init(port_priv, port_idx);
	if (err)
		goto err_port_probe;

	err = register_netdev(port_netdev);
	if (err < 0) {
		dev_err(dev, "register_netdev error %d\n", err);
		goto err_port_probe;
	}

	ethsw->ports[port_idx] = port_priv;

	return 0;

err_port_probe:
	free_netdev(port_netdev);

	return err;
}
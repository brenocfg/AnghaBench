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
struct net_device {int mtu; } ;
struct dpaa2_eth_priv {int /*<<< orphan*/  xdp_prog; } ;

/* Variables and functions */
 int EINVAL ; 
 struct dpaa2_eth_priv* netdev_priv (struct net_device*) ; 
 int set_rx_mfl (struct dpaa2_eth_priv*,int,int) ; 
 int /*<<< orphan*/  xdp_mtu_valid (struct dpaa2_eth_priv*,int) ; 

__attribute__((used)) static int dpaa2_eth_change_mtu(struct net_device *dev, int new_mtu)
{
	struct dpaa2_eth_priv *priv = netdev_priv(dev);
	int err;

	if (!priv->xdp_prog)
		goto out;

	if (!xdp_mtu_valid(priv, new_mtu))
		return -EINVAL;

	err = set_rx_mfl(priv, new_mtu, true);
	if (err)
		return err;

out:
	dev->mtu = new_mtu;
	return 0;
}
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
struct net_device {int /*<<< orphan*/ * phydev; } ;
struct mac_device {int (* stop ) (struct mac_device*) ;int /*<<< orphan*/ * port; } ;
struct dpaa_priv {struct mac_device* mac_dev; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int fman_port_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifdown ; 
 struct dpaa_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_err (struct dpaa_priv*,int /*<<< orphan*/ ,struct net_device*,char*,int) ; 
 int /*<<< orphan*/  netif_tx_stop_all_queues (struct net_device*) ; 
 int /*<<< orphan*/  phy_disconnect (int /*<<< orphan*/ *) ; 
 int stub1 (struct mac_device*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int dpaa_stop(struct net_device *net_dev)
{
	struct mac_device *mac_dev;
	struct dpaa_priv *priv;
	int i, err, error;

	priv = netdev_priv(net_dev);
	mac_dev = priv->mac_dev;

	netif_tx_stop_all_queues(net_dev);
	/* Allow the Fman (Tx) port to process in-flight frames before we
	 * try switching it off.
	 */
	usleep_range(5000, 10000);

	err = mac_dev->stop(mac_dev);
	if (err < 0)
		netif_err(priv, ifdown, net_dev, "mac_dev->stop() = %d\n",
			  err);

	for (i = 0; i < ARRAY_SIZE(mac_dev->port); i++) {
		error = fman_port_disable(mac_dev->port[i]);
		if (error)
			err = error;
	}

	if (net_dev->phydev)
		phy_disconnect(net_dev->phydev);
	net_dev->phydev = NULL;

	return err;
}
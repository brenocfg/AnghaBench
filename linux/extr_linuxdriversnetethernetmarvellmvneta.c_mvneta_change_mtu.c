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
struct mvneta_port {int /*<<< orphan*/  pkt_size; scalar_t__ bm_priv; } ;

/* Variables and functions */
 int ALIGN (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IS_ALIGNED (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MVNETA_RX_PKT_SIZE (int) ; 
 int /*<<< orphan*/  mvneta_bm_update_mtu (struct mvneta_port*,int) ; 
 int /*<<< orphan*/  mvneta_cleanup_rxqs (struct mvneta_port*) ; 
 int /*<<< orphan*/  mvneta_cleanup_txqs (struct mvneta_port*) ; 
 int /*<<< orphan*/  mvneta_percpu_disable ; 
 int /*<<< orphan*/  mvneta_percpu_enable ; 
 int mvneta_setup_rxqs (struct mvneta_port*) ; 
 int mvneta_setup_txqs (struct mvneta_port*) ; 
 int /*<<< orphan*/  mvneta_start_dev (struct mvneta_port*) ; 
 int /*<<< orphan*/  mvneta_stop_dev (struct mvneta_port*) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*,int,int) ; 
 struct mvneta_port* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netdev_update_features (struct net_device*) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 
 int /*<<< orphan*/  on_each_cpu (int /*<<< orphan*/ ,struct mvneta_port*,int) ; 

__attribute__((used)) static int mvneta_change_mtu(struct net_device *dev, int mtu)
{
	struct mvneta_port *pp = netdev_priv(dev);
	int ret;

	if (!IS_ALIGNED(MVNETA_RX_PKT_SIZE(mtu), 8)) {
		netdev_info(dev, "Illegal MTU value %d, rounding to %d\n",
			    mtu, ALIGN(MVNETA_RX_PKT_SIZE(mtu), 8));
		mtu = ALIGN(MVNETA_RX_PKT_SIZE(mtu), 8);
	}

	dev->mtu = mtu;

	if (!netif_running(dev)) {
		if (pp->bm_priv)
			mvneta_bm_update_mtu(pp, mtu);

		netdev_update_features(dev);
		return 0;
	}

	/* The interface is running, so we have to force a
	 * reallocation of the queues
	 */
	mvneta_stop_dev(pp);
	on_each_cpu(mvneta_percpu_disable, pp, true);

	mvneta_cleanup_txqs(pp);
	mvneta_cleanup_rxqs(pp);

	if (pp->bm_priv)
		mvneta_bm_update_mtu(pp, mtu);

	pp->pkt_size = MVNETA_RX_PKT_SIZE(dev->mtu);

	ret = mvneta_setup_rxqs(pp);
	if (ret) {
		netdev_err(dev, "unable to setup rxqs after MTU change\n");
		return ret;
	}

	ret = mvneta_setup_txqs(pp);
	if (ret) {
		netdev_err(dev, "unable to setup txqs after MTU change\n");
		return ret;
	}

	on_each_cpu(mvneta_percpu_enable, pp, true);
	mvneta_start_dev(pp);

	netdev_update_features(dev);

	return 0;
}
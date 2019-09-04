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
struct mvpp2_port {void* pkt_size; } ;

/* Variables and functions */
 int ALIGN (void*,int) ; 
 int /*<<< orphan*/  IS_ALIGNED (void*,int) ; 
 void* MVPP2_RX_PKT_SIZE (int) ; 
 int mvpp2_bm_update_mtu (struct net_device*,int) ; 
 int /*<<< orphan*/  mvpp2_egress_enable (struct mvpp2_port*) ; 
 int /*<<< orphan*/  mvpp2_ingress_enable (struct mvpp2_port*) ; 
 int /*<<< orphan*/  mvpp2_start_dev (struct mvpp2_port*) ; 
 int /*<<< orphan*/  mvpp2_stop_dev (struct mvpp2_port*) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*,int,int) ; 
 struct mvpp2_port* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 

__attribute__((used)) static int mvpp2_change_mtu(struct net_device *dev, int mtu)
{
	struct mvpp2_port *port = netdev_priv(dev);
	int err;

	if (!IS_ALIGNED(MVPP2_RX_PKT_SIZE(mtu), 8)) {
		netdev_info(dev, "illegal MTU value %d, round to %d\n", mtu,
			    ALIGN(MVPP2_RX_PKT_SIZE(mtu), 8));
		mtu = ALIGN(MVPP2_RX_PKT_SIZE(mtu), 8);
	}

	if (!netif_running(dev)) {
		err = mvpp2_bm_update_mtu(dev, mtu);
		if (!err) {
			port->pkt_size =  MVPP2_RX_PKT_SIZE(mtu);
			return 0;
		}

		/* Reconfigure BM to the original MTU */
		err = mvpp2_bm_update_mtu(dev, dev->mtu);
		if (err)
			goto log_error;
	}

	mvpp2_stop_dev(port);

	err = mvpp2_bm_update_mtu(dev, mtu);
	if (!err) {
		port->pkt_size =  MVPP2_RX_PKT_SIZE(mtu);
		goto out_start;
	}

	/* Reconfigure BM to the original MTU */
	err = mvpp2_bm_update_mtu(dev, dev->mtu);
	if (err)
		goto log_error;

out_start:
	mvpp2_start_dev(port);
	mvpp2_egress_enable(port);
	mvpp2_ingress_enable(port);

	return 0;
log_error:
	netdev_err(dev, "failed to change MTU\n");
	return err;
}
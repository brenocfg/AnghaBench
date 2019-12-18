#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct net_device {int mtu; } ;
struct mvpp2_port {scalar_t__ pkt_size; TYPE_2__* dev; struct mvpp2* priv; } ;
struct mvpp2 {int port_count; struct mvpp2_port** port_list; scalar_t__ percpu_pools; } ;
struct TYPE_3__ {int /*<<< orphan*/  parent; } ;
struct TYPE_4__ {int mtu; TYPE_1__ dev; } ;

/* Variables and functions */
 int ALIGN (scalar_t__,int) ; 
 int /*<<< orphan*/  IS_ALIGNED (scalar_t__,int) ; 
 scalar_t__ MVPP2_BM_LONG_PKT_SIZE ; 
 scalar_t__ MVPP2_RX_PKT_SIZE (int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mvpp2_bm_switch_buffers (struct mvpp2*,int) ; 
 int mvpp2_bm_update_mtu (struct net_device*,int) ; 
 int /*<<< orphan*/  mvpp2_egress_enable (struct mvpp2_port*) ; 
 int /*<<< orphan*/  mvpp2_ingress_enable (struct mvpp2_port*) ; 
 int /*<<< orphan*/  mvpp2_start_dev (struct mvpp2_port*) ; 
 int /*<<< orphan*/  mvpp2_stop_dev (struct mvpp2_port*) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*,int,int) ; 
 struct mvpp2_port* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netdev_warn (struct net_device*,char*,int) ; 
 int netif_running (struct net_device*) ; 

__attribute__((used)) static int mvpp2_change_mtu(struct net_device *dev, int mtu)
{
	struct mvpp2_port *port = netdev_priv(dev);
	bool running = netif_running(dev);
	struct mvpp2 *priv = port->priv;
	int err;

	if (!IS_ALIGNED(MVPP2_RX_PKT_SIZE(mtu), 8)) {
		netdev_info(dev, "illegal MTU value %d, round to %d\n", mtu,
			    ALIGN(MVPP2_RX_PKT_SIZE(mtu), 8));
		mtu = ALIGN(MVPP2_RX_PKT_SIZE(mtu), 8);
	}

	if (MVPP2_RX_PKT_SIZE(mtu) > MVPP2_BM_LONG_PKT_SIZE) {
		if (priv->percpu_pools) {
			netdev_warn(dev, "mtu %d too high, switching to shared buffers", mtu);
			mvpp2_bm_switch_buffers(priv, false);
		}
	} else {
		bool jumbo = false;
		int i;

		for (i = 0; i < priv->port_count; i++)
			if (priv->port_list[i] != port &&
			    MVPP2_RX_PKT_SIZE(priv->port_list[i]->dev->mtu) >
			    MVPP2_BM_LONG_PKT_SIZE) {
				jumbo = true;
				break;
			}

		/* No port is using jumbo frames */
		if (!jumbo) {
			dev_info(port->dev->dev.parent,
				 "all ports have a low MTU, switching to per-cpu buffers");
			mvpp2_bm_switch_buffers(priv, true);
		}
	}

	if (running)
		mvpp2_stop_dev(port);

	err = mvpp2_bm_update_mtu(dev, mtu);
	if (err) {
		netdev_err(dev, "failed to change MTU\n");
		/* Reconfigure BM to the original MTU */
		mvpp2_bm_update_mtu(dev, dev->mtu);
	} else {
		port->pkt_size =  MVPP2_RX_PKT_SIZE(mtu);
	}

	if (running) {
		mvpp2_start_dev(port);
		mvpp2_egress_enable(port);
		mvpp2_ingress_enable(port);
	}

	return err;
}
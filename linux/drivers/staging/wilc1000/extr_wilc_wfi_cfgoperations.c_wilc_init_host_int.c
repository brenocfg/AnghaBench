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
struct wilc_priv {int p2p_listen_state; int /*<<< orphan*/  hif_drv; int /*<<< orphan*/  scan_req_lock; } ;
struct wilc_vif {struct wilc_priv priv; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 struct wilc_vif* netdev_priv (struct net_device*) ; 
 int wilc_init (struct net_device*,int /*<<< orphan*/ *) ; 

int wilc_init_host_int(struct net_device *net)
{
	int ret;
	struct wilc_vif *vif = netdev_priv(net);
	struct wilc_priv *priv = &vif->priv;

	priv->p2p_listen_state = false;

	mutex_init(&priv->scan_req_lock);
	ret = wilc_init(net, &priv->hif_drv);
	if (ret)
		netdev_err(net, "Error while initializing hostinterface\n");

	return ret;
}
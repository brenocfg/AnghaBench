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
struct wilc_priv {int p2p_listen_state; int /*<<< orphan*/  scan_req_lock; } ;
struct wilc_vif {TYPE_1__* wilc; struct wilc_priv priv; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  hif_workqueue; } ;

/* Variables and functions */
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 struct wilc_vif* netdev_priv (struct net_device*) ; 
 int wilc_deinit (struct wilc_vif*) ; 

void wilc_deinit_host_int(struct net_device *net)
{
	int ret;
	struct wilc_vif *vif = netdev_priv(net);
	struct wilc_priv *priv = &vif->priv;

	priv->p2p_listen_state = false;

	flush_workqueue(vif->wilc->hif_workqueue);
	mutex_destroy(&priv->scan_req_lock);
	ret = wilc_deinit(vif);

	if (ret)
		netdev_err(net, "Error while deinitializing host interface\n");
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u16 ;
struct net_device {int dummy; } ;
struct cpsw_priv {TYPE_3__* ndev; int /*<<< orphan*/  mac_addr; int /*<<< orphan*/  dev; struct cpsw_common* cpsw; } ;
struct TYPE_4__ {scalar_t__ default_vlan; int slaves; scalar_t__ dual_emac; } ;
struct cpsw_common {int /*<<< orphan*/  dev; int /*<<< orphan*/  ale; TYPE_2__* slaves; TYPE_1__ data; } ;
typedef  int /*<<< orphan*/  __be16 ;
struct TYPE_6__ {int /*<<< orphan*/  broadcast; } ;
struct TYPE_5__ {scalar_t__ port_vlan; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALE_VLAN ; 
 int /*<<< orphan*/  HOST_PORT_NUM ; 
 int cpsw_ale_del_mcast (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int cpsw_ale_del_ucast (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int cpsw_ale_del_vlan (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int cpsw_ale_flush_multicast (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 struct cpsw_priv* netdev_priv (struct net_device*) ; 
 int pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_noidle (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cpsw_ndo_vlan_rx_kill_vid(struct net_device *ndev,
				     __be16 proto, u16 vid)
{
	struct cpsw_priv *priv = netdev_priv(ndev);
	struct cpsw_common *cpsw = priv->cpsw;
	int ret;

	if (vid == cpsw->data.default_vlan)
		return 0;

	ret = pm_runtime_get_sync(cpsw->dev);
	if (ret < 0) {
		pm_runtime_put_noidle(cpsw->dev);
		return ret;
	}

	if (cpsw->data.dual_emac) {
		int i;

		for (i = 0; i < cpsw->data.slaves; i++) {
			if (vid == cpsw->slaves[i].port_vlan)
				goto err;
		}
	}

	dev_info(priv->dev, "removing vlanid %d from vlan filter\n", vid);
	ret = cpsw_ale_del_vlan(cpsw->ale, vid, 0);
	ret |= cpsw_ale_del_ucast(cpsw->ale, priv->mac_addr,
				  HOST_PORT_NUM, ALE_VLAN, vid);
	ret |= cpsw_ale_del_mcast(cpsw->ale, priv->ndev->broadcast,
				  0, ALE_VLAN, vid);
	ret |= cpsw_ale_flush_multicast(cpsw->ale, 0, vid);
err:
	pm_runtime_put(cpsw->dev);
	return ret;
}
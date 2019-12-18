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
typedef  int /*<<< orphan*/  u16 ;
struct sockaddr {int /*<<< orphan*/  sa_data; } ;
struct net_device {int /*<<< orphan*/  dev_addr; } ;
struct cpsw_priv {size_t emac_port; int /*<<< orphan*/  mac_addr; struct cpsw_common* cpsw; } ;
struct TYPE_3__ {scalar_t__ dual_emac; } ;
struct cpsw_common {int /*<<< orphan*/  dev; int /*<<< orphan*/  ale; TYPE_2__* slaves; TYPE_1__ data; } ;
struct TYPE_4__ {int /*<<< orphan*/  port_vlan; } ;

/* Variables and functions */
 int ALE_VLAN ; 
 int EADDRNOTAVAIL ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  HOST_PORT_NUM ; 
 int /*<<< orphan*/  cpsw_ale_add_ucast (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpsw_ale_del_ucast (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpsw_set_slave_mac ; 
 int /*<<< orphan*/  for_each_slave (struct cpsw_priv*,int /*<<< orphan*/ ,struct cpsw_priv*) ; 
 int /*<<< orphan*/  is_valid_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct cpsw_priv* netdev_priv (struct net_device*) ; 
 int pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_noidle (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cpsw_ndo_set_mac_address(struct net_device *ndev, void *p)
{
	struct cpsw_priv *priv = netdev_priv(ndev);
	struct sockaddr *addr = (struct sockaddr *)p;
	struct cpsw_common *cpsw = priv->cpsw;
	int flags = 0;
	u16 vid = 0;
	int ret;

	if (!is_valid_ether_addr(addr->sa_data))
		return -EADDRNOTAVAIL;

	ret = pm_runtime_get_sync(cpsw->dev);
	if (ret < 0) {
		pm_runtime_put_noidle(cpsw->dev);
		return ret;
	}

	if (cpsw->data.dual_emac) {
		vid = cpsw->slaves[priv->emac_port].port_vlan;
		flags = ALE_VLAN;
	}

	cpsw_ale_del_ucast(cpsw->ale, priv->mac_addr, HOST_PORT_NUM,
			   flags, vid);
	cpsw_ale_add_ucast(cpsw->ale, addr->sa_data, HOST_PORT_NUM,
			   flags, vid);

	memcpy(priv->mac_addr, addr->sa_data, ETH_ALEN);
	memcpy(ndev->dev_addr, priv->mac_addr, ETH_ALEN);
	for_each_slave(priv, cpsw_set_slave_mac, priv);

	pm_runtime_put(cpsw->dev);

	return 0;
}
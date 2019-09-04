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
struct xgbe_vxlan_data {int /*<<< orphan*/  list; int /*<<< orphan*/  port; int /*<<< orphan*/  sa_family; } ;
struct TYPE_2__ {int /*<<< orphan*/  vxn; } ;
struct xgbe_prv_data {int vxlan_port_count; int vxlan_force_disable; int /*<<< orphan*/  vxlan_ports; TYPE_1__ hw_feat; } ;
struct udp_tunnel_info {scalar_t__ type; int /*<<< orphan*/  port; int /*<<< orphan*/  sa_family; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ UDP_TUNNEL_TYPE_VXLAN ; 
 int /*<<< orphan*/  be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drv ; 
 struct xgbe_vxlan_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct xgbe_prv_data* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_dbg (struct xgbe_prv_data*,int /*<<< orphan*/ ,struct net_device*,char*,...) ; 
 int /*<<< orphan*/  xgbe_disable_vxlan_accel (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  xgbe_enable_vxlan_accel (struct xgbe_prv_data*) ; 

__attribute__((used)) static void xgbe_udp_tunnel_add(struct net_device *netdev,
				struct udp_tunnel_info *ti)
{
	struct xgbe_prv_data *pdata = netdev_priv(netdev);
	struct xgbe_vxlan_data *vdata;

	if (!pdata->hw_feat.vxn)
		return;

	if (ti->type != UDP_TUNNEL_TYPE_VXLAN)
		return;

	pdata->vxlan_port_count++;

	netif_dbg(pdata, drv, netdev,
		  "adding VXLAN tunnel, family=%hx/port=%hx\n",
		  ti->sa_family, be16_to_cpu(ti->port));

	if (pdata->vxlan_force_disable)
		return;

	vdata = kzalloc(sizeof(*vdata), GFP_ATOMIC);
	if (!vdata) {
		/* Can no longer properly track VXLAN ports */
		pdata->vxlan_force_disable = 1;
		netif_dbg(pdata, drv, netdev,
			  "internal error, disabling VXLAN accelerations\n");

		xgbe_disable_vxlan_accel(pdata);

		return;
	}
	vdata->sa_family = ti->sa_family;
	vdata->port = ti->port;

	list_add_tail(&vdata->list, &pdata->vxlan_ports);

	/* First port added? */
	if (pdata->vxlan_port_count == 1) {
		xgbe_enable_vxlan_accel(pdata);

		return;
	}
}
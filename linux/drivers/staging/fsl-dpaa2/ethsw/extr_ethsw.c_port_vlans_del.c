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
struct TYPE_2__ {int /*<<< orphan*/  orig_dev; } ;
struct switchdev_obj_port_vlan {int vid_begin; int vid_end; TYPE_1__ obj; } ;
struct net_device {int dummy; } ;
struct ethsw_port_priv {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int ethsw_port_del_vlan (struct ethsw_port_priv*,int) ; 
 struct ethsw_port_priv* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_is_bridge_master (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int port_vlans_del(struct net_device *netdev,
			  const struct switchdev_obj_port_vlan *vlan)
{
	struct ethsw_port_priv *port_priv = netdev_priv(netdev);
	int vid, err = 0;

	if (netif_is_bridge_master(vlan->obj.orig_dev))
		return -EOPNOTSUPP;

	for (vid = vlan->vid_begin; vid <= vlan->vid_end; vid++) {
		err = ethsw_port_del_vlan(port_priv, vid);
		if (err)
			break;
	}

	return err;
}
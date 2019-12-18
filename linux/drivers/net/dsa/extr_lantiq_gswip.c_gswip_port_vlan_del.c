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
typedef  scalar_t__ u16 ;
struct switchdev_obj_port_vlan {int flags; scalar_t__ vid_begin; scalar_t__ vid_end; } ;
struct net_device {int dummy; } ;
struct gswip_priv {int dummy; } ;
struct dsa_switch {struct gswip_priv* priv; } ;
struct TYPE_2__ {struct net_device* bridge_dev; } ;

/* Variables and functions */
 int BRIDGE_VLAN_INFO_PVID ; 
 scalar_t__ dsa_is_cpu_port (struct dsa_switch*,int) ; 
 TYPE_1__* dsa_to_port (struct dsa_switch*,int) ; 
 int gswip_vlan_remove (struct gswip_priv*,struct net_device*,int,scalar_t__,int,int) ; 

__attribute__((used)) static int gswip_port_vlan_del(struct dsa_switch *ds, int port,
			       const struct switchdev_obj_port_vlan *vlan)
{
	struct gswip_priv *priv = ds->priv;
	struct net_device *bridge = dsa_to_port(ds, port)->bridge_dev;
	bool pvid = vlan->flags & BRIDGE_VLAN_INFO_PVID;
	u16 vid;
	int err;

	/* We have to receive all packets on the CPU port and should not
	 * do any VLAN filtering here. This is also called with bridge
	 * NULL and then we do not know for which bridge to configure
	 * this.
	 */
	if (dsa_is_cpu_port(ds, port))
		return 0;

	for (vid = vlan->vid_begin; vid <= vlan->vid_end; ++vid) {
		err = gswip_vlan_remove(priv, bridge, port, vid, pvid, true);
		if (err)
			return err;
	}

	return 0;
}
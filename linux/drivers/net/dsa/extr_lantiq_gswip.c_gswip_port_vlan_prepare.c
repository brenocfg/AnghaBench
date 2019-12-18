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
struct switchdev_obj_port_vlan {scalar_t__ vid_begin; scalar_t__ vid_end; } ;
struct net_device {int dummy; } ;
struct gswip_priv {TYPE_3__* vlans; TYPE_1__* hw_info; } ;
struct dsa_switch {struct gswip_priv* priv; } ;
struct TYPE_6__ {scalar_t__ vid; struct net_device* bridge; } ;
struct TYPE_5__ {struct net_device* bridge_dev; } ;
struct TYPE_4__ {unsigned int max_ports; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_3__*) ; 
 int ENOSPC ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  dsa_is_cpu_port (struct dsa_switch*,int) ; 
 TYPE_2__* dsa_to_port (struct dsa_switch*,int) ; 

__attribute__((used)) static int gswip_port_vlan_prepare(struct dsa_switch *ds, int port,
				   const struct switchdev_obj_port_vlan *vlan)
{
	struct gswip_priv *priv = ds->priv;
	struct net_device *bridge = dsa_to_port(ds, port)->bridge_dev;
	unsigned int max_ports = priv->hw_info->max_ports;
	u16 vid;
	int i;
	int pos = max_ports;

	/* We only support VLAN filtering on bridges */
	if (!dsa_is_cpu_port(ds, port) && !bridge)
		return -EOPNOTSUPP;

	for (vid = vlan->vid_begin; vid <= vlan->vid_end; ++vid) {
		int idx = -1;

		/* Check if there is already a page for this VLAN */
		for (i = max_ports; i < ARRAY_SIZE(priv->vlans); i++) {
			if (priv->vlans[i].bridge == bridge &&
			    priv->vlans[i].vid == vid) {
				idx = i;
				break;
			}
		}

		/* If this VLAN is not programmed yet, we have to reserve
		 * one entry in the VLAN table. Make sure we start at the
		 * next position round.
		 */
		if (idx == -1) {
			/* Look for a free slot */
			for (; pos < ARRAY_SIZE(priv->vlans); pos++) {
				if (!priv->vlans[pos].bridge) {
					idx = pos;
					pos++;
					break;
				}
			}

			if (idx == -1)
				return -ENOSPC;
		}
	}

	return 0;
}
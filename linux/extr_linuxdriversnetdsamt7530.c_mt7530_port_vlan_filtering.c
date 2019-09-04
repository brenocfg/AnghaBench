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
struct mt7530_priv {TYPE_1__* ports; } ;
struct dsa_switch {struct mt7530_priv* priv; } ;
struct TYPE_2__ {int vlan_filtering; } ;

/* Variables and functions */
 int MT7530_CPU_PORT ; 
 int /*<<< orphan*/  mt7530_port_set_vlan_aware (struct dsa_switch*,int) ; 

__attribute__((used)) static int
mt7530_port_vlan_filtering(struct dsa_switch *ds, int port,
			   bool vlan_filtering)
{
	struct mt7530_priv *priv = ds->priv;

	priv->ports[port].vlan_filtering = vlan_filtering;

	if (vlan_filtering) {
		/* The port is being kept as VLAN-unaware port when bridge is
		 * set up with vlan_filtering not being set, Otherwise, the
		 * port and the corresponding CPU port is required the setup
		 * for becoming a VLAN-aware port.
		 */
		mt7530_port_set_vlan_aware(ds, port);
		mt7530_port_set_vlan_aware(ds, MT7530_CPU_PORT);
	}

	return 0;
}
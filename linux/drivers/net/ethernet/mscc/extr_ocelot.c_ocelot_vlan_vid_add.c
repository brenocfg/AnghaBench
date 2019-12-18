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
typedef  size_t u16 ;
struct ocelot_port {size_t pvid; size_t vid; int /*<<< orphan*/  chip_port; struct ocelot* ocelot; } ;
struct ocelot {int /*<<< orphan*/  dev; int /*<<< orphan*/ * vlan_mask; } ;
struct net_device {int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int EBUSY ; 
 int /*<<< orphan*/  ENTRYTYPE_LOCKED ; 
 int /*<<< orphan*/  PGID_CPU ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,size_t) ; 
 struct ocelot_port* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  ocelot_mact_learn (struct ocelot*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocelot_vlan_port_apply (struct ocelot*,struct ocelot_port*) ; 
 int ocelot_vlant_set_mask (struct ocelot*,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ocelot_vlan_vid_add(struct net_device *dev, u16 vid, bool pvid,
			       bool untagged)
{
	struct ocelot_port *port = netdev_priv(dev);
	struct ocelot *ocelot = port->ocelot;
	int ret;

	/* Add the port MAC address to with the right VLAN information */
	ocelot_mact_learn(ocelot, PGID_CPU, dev->dev_addr, vid,
			  ENTRYTYPE_LOCKED);

	/* Make the port a member of the VLAN */
	ocelot->vlan_mask[vid] |= BIT(port->chip_port);
	ret = ocelot_vlant_set_mask(ocelot, vid, ocelot->vlan_mask[vid]);
	if (ret)
		return ret;

	/* Default ingress vlan classification */
	if (pvid)
		port->pvid = vid;

	/* Untagged egress vlan clasification */
	if (untagged && port->vid != vid) {
		if (port->vid) {
			dev_err(ocelot->dev,
				"Port already has a native VLAN: %d\n",
				port->vid);
			return -EBUSY;
		}
		port->vid = vid;
	}

	ocelot_vlan_port_apply(ocelot, port);

	return 0;
}
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
typedef  scalar_t__ u16 ;
struct switchdev_trans {int dummy; } ;
struct switchdev_obj_port_mdb {unsigned char* addr; scalar_t__ vid; } ;
struct ocelot_port {int /*<<< orphan*/  chip_port; scalar_t__ pvid; struct ocelot* ocelot; } ;
struct ocelot_multicast {unsigned char* addr; unsigned char ports; int /*<<< orphan*/  list; scalar_t__ vid; } ;
struct ocelot {int /*<<< orphan*/  multicast; int /*<<< orphan*/  dev; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  ENTRYTYPE_MACv4 ; 
 int ETH_ALEN ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct ocelot_multicast* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,int) ; 
 struct ocelot_port* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  ocelot_mact_forget (struct ocelot*,unsigned char*,scalar_t__) ; 
 int ocelot_mact_learn (struct ocelot*,int /*<<< orphan*/ ,unsigned char*,scalar_t__,int /*<<< orphan*/ ) ; 
 struct ocelot_multicast* ocelot_multicast_get (struct ocelot*,unsigned char*,scalar_t__) ; 

__attribute__((used)) static int ocelot_port_obj_add_mdb(struct net_device *dev,
				   const struct switchdev_obj_port_mdb *mdb,
				   struct switchdev_trans *trans)
{
	struct ocelot_port *port = netdev_priv(dev);
	struct ocelot *ocelot = port->ocelot;
	struct ocelot_multicast *mc;
	unsigned char addr[ETH_ALEN];
	u16 vid = mdb->vid;
	bool new = false;

	if (!vid)
		vid = port->pvid;

	mc = ocelot_multicast_get(ocelot, mdb->addr, vid);
	if (!mc) {
		mc = devm_kzalloc(ocelot->dev, sizeof(*mc), GFP_KERNEL);
		if (!mc)
			return -ENOMEM;

		memcpy(mc->addr, mdb->addr, ETH_ALEN);
		mc->vid = vid;

		list_add_tail(&mc->list, &ocelot->multicast);
		new = true;
	}

	memcpy(addr, mc->addr, ETH_ALEN);
	addr[0] = 0;

	if (!new) {
		addr[2] = mc->ports << 0;
		addr[1] = mc->ports << 8;
		ocelot_mact_forget(ocelot, addr, vid);
	}

	mc->ports |= BIT(port->chip_port);
	addr[2] = mc->ports << 0;
	addr[1] = mc->ports << 8;

	return ocelot_mact_learn(ocelot, 0, addr, vid, ENTRYTYPE_MACv4);
}
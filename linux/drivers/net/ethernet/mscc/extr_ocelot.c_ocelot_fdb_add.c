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
typedef  int /*<<< orphan*/  u16 ;
struct ocelot_port {int /*<<< orphan*/  chip_port; int /*<<< orphan*/  pvid; int /*<<< orphan*/  vlan_aware; struct ocelot* ocelot; } ;
struct ocelot {int dummy; } ;
struct nlattr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct net_device {int dummy; } ;
struct ndmsg {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ENTRYTYPE_LOCKED ; 
 struct ocelot_port* netdev_priv (struct net_device*) ; 
 int ocelot_mact_learn (struct ocelot*,int /*<<< orphan*/ ,unsigned char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ocelot_fdb_add(struct ndmsg *ndm, struct nlattr *tb[],
			  struct net_device *dev, const unsigned char *addr,
			  u16 vid, u16 flags,
			  struct netlink_ext_ack *extack)
{
	struct ocelot_port *port = netdev_priv(dev);
	struct ocelot *ocelot = port->ocelot;

	if (!vid) {
		if (!port->vlan_aware)
			/* If the bridge is not VLAN aware and no VID was
			 * provided, set it to pvid to ensure the MAC entry
			 * matches incoming untagged packets
			 */
			vid = port->pvid;
		else
			/* If the bridge is VLAN aware a VID must be provided as
			 * otherwise the learnt entry wouldn't match any frame.
			 */
			return -EINVAL;
	}

	return ocelot_mact_learn(ocelot, port->chip_port, addr, vid,
				 ENTRYTYPE_LOCKED);
}
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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct ofdpa_port {int /*<<< orphan*/  dev; int /*<<< orphan*/  pport; int /*<<< orphan*/  vlan_bitmap; struct ofdpa* ofdpa; } ;
struct ofdpa {TYPE_1__* rocker; } ;
typedef  int /*<<< orphan*/  __be16 ;
struct TYPE_2__ {unsigned int port_count; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  ROCKER_GROUP_L2_FLOOD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ROCKER_GROUP_L2_INTERFACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * kcalloc (unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 int ofdpa_group_l2_flood (struct ofdpa_port*,int,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct ofdpa_port* ofdpa_port_get (struct ofdpa const*,int) ; 
 int /*<<< orphan*/  ofdpa_port_is_bridged (struct ofdpa_port*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ofdpa_port_vlan_flood_group(struct ofdpa_port *ofdpa_port,
				       int flags, __be16 vlan_id)
{
	struct ofdpa_port *p;
	const struct ofdpa *ofdpa = ofdpa_port->ofdpa;
	unsigned int port_count = ofdpa->rocker->port_count;
	u32 group_id = ROCKER_GROUP_L2_FLOOD(vlan_id, 0);
	u32 *group_ids;
	u8 group_count = 0;
	int err = 0;
	int i;

	group_ids = kcalloc(port_count, sizeof(u32), GFP_KERNEL);
	if (!group_ids)
		return -ENOMEM;

	/* Adjust the flood group for this VLAN.  The flood group
	 * references an L2 interface group for each port in this
	 * VLAN.
	 */

	for (i = 0; i < port_count; i++) {
		p = ofdpa_port_get(ofdpa, i);
		if (!p)
			continue;
		if (!ofdpa_port_is_bridged(p))
			continue;
		if (test_bit(ntohs(vlan_id), p->vlan_bitmap)) {
			group_ids[group_count++] =
				ROCKER_GROUP_L2_INTERFACE(vlan_id, p->pport);
		}
	}

	/* If there are no bridged ports in this VLAN, we're done */
	if (group_count == 0)
		goto no_ports_in_vlan;

	err = ofdpa_group_l2_flood(ofdpa_port, flags, vlan_id,
				   group_count, group_ids, group_id);
	if (err)
		netdev_err(ofdpa_port->dev, "Error (%d) port VLAN l2 flood group\n", err);

no_ports_in_vlan:
	kfree(group_ids);
	return err;
}
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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct ofdpa_port {TYPE_1__* dev; int /*<<< orphan*/  pport; int /*<<< orphan*/  internal_vlan_id; struct ofdpa* ofdpa; } ;
struct ofdpa_neigh_tbl_entry {int ttl_check; int /*<<< orphan*/  ip_addr; int /*<<< orphan*/  index; int /*<<< orphan*/  eth_dst; TYPE_1__* dev; } ;
struct ofdpa {int /*<<< orphan*/  neigh_tbl_lock; } ;
typedef  enum rocker_of_dpa_table_id { ____Placeholder_rocker_of_dpa_table_id } rocker_of_dpa_table_id ;
typedef  int /*<<< orphan*/  __be32 ;
typedef  int /*<<< orphan*/  __be16 ;
struct TYPE_2__ {int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  ETH_P_IP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int OFDPA_OP_FLAG_REMOVE ; 
 int /*<<< orphan*/  ROCKER_GROUP_L3_UNICAST (int /*<<< orphan*/ ) ; 
 int ROCKER_OF_DPA_TABLE_ID_ACL_POLICY ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inet_make_mask (int) ; 
 int /*<<< orphan*/  kfree (struct ofdpa_neigh_tbl_entry*) ; 
 struct ofdpa_neigh_tbl_entry* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct ofdpa_neigh_tbl_entry*,struct ofdpa_neigh_tbl_entry*,int) ; 
 int /*<<< orphan*/  netdev_err (TYPE_1__*,char*,int,int /*<<< orphan*/ *,...) ; 
 int ofdpa_flow_tbl_ucast4_routing (struct ofdpa_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int ofdpa_group_l3_unicast (struct ofdpa_port*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofdpa_neigh_add (struct ofdpa*,struct ofdpa_neigh_tbl_entry*) ; 
 int /*<<< orphan*/  ofdpa_neigh_del (struct ofdpa_neigh_tbl_entry*) ; 
 struct ofdpa_neigh_tbl_entry* ofdpa_neigh_tbl_find (struct ofdpa*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofdpa_neigh_update (struct ofdpa_neigh_tbl_entry*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int ofdpa_port_ipv4_neigh(struct ofdpa_port *ofdpa_port,
				 int flags, __be32 ip_addr, const u8 *eth_dst)
{
	struct ofdpa *ofdpa = ofdpa_port->ofdpa;
	struct ofdpa_neigh_tbl_entry *entry;
	struct ofdpa_neigh_tbl_entry *found;
	unsigned long lock_flags;
	__be16 eth_type = htons(ETH_P_IP);
	enum rocker_of_dpa_table_id goto_tbl =
			ROCKER_OF_DPA_TABLE_ID_ACL_POLICY;
	u32 group_id;
	u32 priority = 0;
	bool adding = !(flags & OFDPA_OP_FLAG_REMOVE);
	bool updating;
	bool removing;
	int err = 0;

	entry = kzalloc(sizeof(*entry), GFP_KERNEL);
	if (!entry)
		return -ENOMEM;

	spin_lock_irqsave(&ofdpa->neigh_tbl_lock, lock_flags);

	found = ofdpa_neigh_tbl_find(ofdpa, ip_addr);

	updating = found && adding;
	removing = found && !adding;
	adding = !found && adding;

	if (adding) {
		entry->ip_addr = ip_addr;
		entry->dev = ofdpa_port->dev;
		ether_addr_copy(entry->eth_dst, eth_dst);
		entry->ttl_check = true;
		ofdpa_neigh_add(ofdpa, entry);
	} else if (removing) {
		memcpy(entry, found, sizeof(*entry));
		ofdpa_neigh_del(found);
	} else if (updating) {
		ofdpa_neigh_update(found, eth_dst, true);
		memcpy(entry, found, sizeof(*entry));
	} else {
		err = -ENOENT;
	}

	spin_unlock_irqrestore(&ofdpa->neigh_tbl_lock, lock_flags);

	if (err)
		goto err_out;

	/* For each active neighbor, we have an L3 unicast group and
	 * a /32 route to the neighbor, which uses the L3 unicast
	 * group.  The L3 unicast group can also be referred to by
	 * other routes' nexthops.
	 */

	err = ofdpa_group_l3_unicast(ofdpa_port, flags,
				     entry->index,
				     ofdpa_port->dev->dev_addr,
				     entry->eth_dst,
				     ofdpa_port->internal_vlan_id,
				     entry->ttl_check,
				     ofdpa_port->pport);
	if (err) {
		netdev_err(ofdpa_port->dev, "Error (%d) L3 unicast group index %d\n",
			   err, entry->index);
		goto err_out;
	}

	if (adding || removing) {
		group_id = ROCKER_GROUP_L3_UNICAST(entry->index);
		err = ofdpa_flow_tbl_ucast4_routing(ofdpa_port,
						    eth_type, ip_addr,
						    inet_make_mask(32),
						    priority, goto_tbl,
						    group_id, NULL, flags);

		if (err)
			netdev_err(ofdpa_port->dev, "Error (%d) /32 unicast route %pI4 group 0x%08x\n",
				   err, &entry->ip_addr, group_id);
	}

err_out:
	if (!adding)
		kfree(entry);

	return err;
}
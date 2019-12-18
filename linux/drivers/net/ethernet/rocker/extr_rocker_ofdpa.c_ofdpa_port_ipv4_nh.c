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
typedef  int /*<<< orphan*/  u32 ;
struct ofdpa_port {int /*<<< orphan*/  dev; struct ofdpa* ofdpa; } ;
struct ofdpa_neigh_tbl_entry {int /*<<< orphan*/  index; int /*<<< orphan*/  eth_dst; int /*<<< orphan*/  dev; int /*<<< orphan*/  ip_addr; } ;
struct ofdpa {int /*<<< orphan*/  neigh_tbl_lock; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int OFDPA_OP_FLAG_REMOVE ; 
 int /*<<< orphan*/  is_zero_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct ofdpa_neigh_tbl_entry*) ; 
 struct ofdpa_neigh_tbl_entry* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofdpa_neigh_add (struct ofdpa*,struct ofdpa_neigh_tbl_entry*) ; 
 int /*<<< orphan*/  ofdpa_neigh_del (struct ofdpa_neigh_tbl_entry*) ; 
 struct ofdpa_neigh_tbl_entry* ofdpa_neigh_tbl_find (struct ofdpa*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofdpa_neigh_update (struct ofdpa_neigh_tbl_entry*,int /*<<< orphan*/ *,int) ; 
 int ofdpa_port_ipv4_resolve (struct ofdpa_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int ofdpa_port_ipv4_nh(struct ofdpa_port *ofdpa_port,
			      int flags, __be32 ip_addr, u32 *index)
{
	struct ofdpa *ofdpa = ofdpa_port->ofdpa;
	struct ofdpa_neigh_tbl_entry *entry;
	struct ofdpa_neigh_tbl_entry *found;
	unsigned long lock_flags;
	bool adding = !(flags & OFDPA_OP_FLAG_REMOVE);
	bool updating;
	bool removing;
	bool resolved = true;
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
		ofdpa_neigh_add(ofdpa, entry);
		*index = entry->index;
		resolved = false;
	} else if (removing) {
		*index = found->index;
		ofdpa_neigh_del(found);
	} else if (updating) {
		ofdpa_neigh_update(found, NULL, false);
		resolved = !is_zero_ether_addr(found->eth_dst);
		*index = found->index;
	} else {
		err = -ENOENT;
	}

	spin_unlock_irqrestore(&ofdpa->neigh_tbl_lock, lock_flags);

	if (!adding)
		kfree(entry);

	if (err)
		return err;

	/* Resolved means neigh ip_addr is resolved to neigh mac. */

	if (!resolved)
		err = ofdpa_port_ipv4_resolve(ofdpa_port, ip_addr);

	return err;
}
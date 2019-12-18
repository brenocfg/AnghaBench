#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct net_device {int /*<<< orphan*/ * dev_addr; } ;
struct neighbour {TYPE_3__* dev; scalar_t__ primary_key; TYPE_1__* tbl; } ;
struct l2t_entry {int ifindex; scalar_t__ lport; int hash; int v6; int /*<<< orphan*/  lock; struct l2t_entry* next; int /*<<< orphan*/  vlan; int /*<<< orphan*/  refcnt; int /*<<< orphan*/  addr; int /*<<< orphan*/  dmac; int /*<<< orphan*/  state; } ;
struct l2t_data {int /*<<< orphan*/  lock; TYPE_2__* l2tab; } ;
struct TYPE_10__ {scalar_t__ tx_chan; scalar_t__ lport; } ;
struct TYPE_9__ {int ifindex; int flags; } ;
struct TYPE_8__ {struct l2t_entry* first; } ;
struct TYPE_7__ {unsigned int key_len; } ;

/* Variables and functions */
 int IFF_LOOPBACK ; 
 int /*<<< orphan*/  L2T_STATE_RESOLVING ; 
 int /*<<< orphan*/  VLAN_NONE ; 
 int addr_hash (struct l2t_data*,int /*<<< orphan*/ *,unsigned int,int) ; 
 int /*<<< orphan*/  addreq (struct l2t_entry*,int /*<<< orphan*/ *) ; 
 struct l2t_entry* alloc_l2e (struct l2t_data*) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 scalar_t__ is_vlan_dev (TYPE_3__*) ; 
 int /*<<< orphan*/  l2t_hold (struct l2t_data*,struct l2t_entry*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  neigh_replace (struct l2t_entry*,struct neighbour*) ; 
 TYPE_5__* netdev2pinfo (struct net_device const*) ; 
 int /*<<< orphan*/  reuse_entry (struct l2t_entry*,struct neighbour*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlan_dev_get_egress_qos_mask (TYPE_3__*,unsigned int) ; 
 int /*<<< orphan*/  vlan_dev_vlan_id (TYPE_3__*) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

struct l2t_entry *cxgb4_l2t_get(struct l2t_data *d, struct neighbour *neigh,
				const struct net_device *physdev,
				unsigned int priority)
{
	u8 lport;
	u16 vlan;
	struct l2t_entry *e;
	unsigned int addr_len = neigh->tbl->key_len;
	u32 *addr = (u32 *)neigh->primary_key;
	int ifidx = neigh->dev->ifindex;
	int hash = addr_hash(d, addr, addr_len, ifidx);

	if (neigh->dev->flags & IFF_LOOPBACK)
		lport = netdev2pinfo(physdev)->tx_chan + 4;
	else
		lport = netdev2pinfo(physdev)->lport;

	if (is_vlan_dev(neigh->dev)) {
		vlan = vlan_dev_vlan_id(neigh->dev);
		vlan |= vlan_dev_get_egress_qos_mask(neigh->dev, priority);
	} else {
		vlan = VLAN_NONE;
	}

	write_lock_bh(&d->lock);
	for (e = d->l2tab[hash].first; e; e = e->next)
		if (!addreq(e, addr) && e->ifindex == ifidx &&
		    e->vlan == vlan && e->lport == lport) {
			l2t_hold(d, e);
			if (atomic_read(&e->refcnt) == 1)
				reuse_entry(e, neigh);
			goto done;
		}

	/* Need to allocate a new entry */
	e = alloc_l2e(d);
	if (e) {
		spin_lock(&e->lock);          /* avoid race with t4_l2t_free */
		e->state = L2T_STATE_RESOLVING;
		if (neigh->dev->flags & IFF_LOOPBACK)
			memcpy(e->dmac, physdev->dev_addr, sizeof(e->dmac));
		memcpy(e->addr, addr, addr_len);
		e->ifindex = ifidx;
		e->hash = hash;
		e->lport = lport;
		e->v6 = addr_len == 16;
		atomic_set(&e->refcnt, 1);
		neigh_replace(e, neigh);
		e->vlan = vlan;
		e->next = d->l2tab[hash].first;
		d->l2tab[hash].first = e;
		spin_unlock(&e->lock);
	}
done:
	write_unlock_bh(&d->lock);
	return e;
}
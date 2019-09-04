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
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff_head {int dummy; } ;
struct neighbour {int nud_state; int /*<<< orphan*/  ha; TYPE_2__* dev; scalar_t__ primary_key; TYPE_1__* tbl; } ;
struct l2t_entry {int ifindex; scalar_t__ state; int /*<<< orphan*/  lock; int /*<<< orphan*/  dmac; struct sk_buff_head arpq; struct neighbour* neigh; int /*<<< orphan*/  refcnt; struct l2t_entry* next; } ;
struct l2t_data {int /*<<< orphan*/  lock; TYPE_3__* l2tab; } ;
struct adapter {struct l2t_data* l2t; } ;
struct TYPE_6__ {struct l2t_entry* first; } ;
struct TYPE_5__ {int ifindex; } ;
struct TYPE_4__ {unsigned int key_len; } ;

/* Variables and functions */
 scalar_t__ L2T_STATE_RESOLVING ; 
 scalar_t__ L2T_STATE_STALE ; 
 scalar_t__ L2T_STATE_VALID ; 
 int NUD_CONNECTED ; 
 int NUD_FAILED ; 
 int NUD_STALE ; 
 int addr_hash (struct l2t_data*,int /*<<< orphan*/ *,unsigned int,int) ; 
 int /*<<< orphan*/  addreq (struct l2t_entry*,int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  handle_failed_resolution (struct adapter*,struct l2t_entry*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  neigh_replace (struct l2t_entry*,struct neighbour*) ; 
 int /*<<< orphan*/  read_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_empty (struct sk_buff_head*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_l2e (struct adapter*,struct l2t_entry*,int) ; 

void t4_l2t_update(struct adapter *adap, struct neighbour *neigh)
{
	struct l2t_entry *e;
	struct sk_buff_head *arpq = NULL;
	struct l2t_data *d = adap->l2t;
	unsigned int addr_len = neigh->tbl->key_len;
	u32 *addr = (u32 *) neigh->primary_key;
	int ifidx = neigh->dev->ifindex;
	int hash = addr_hash(d, addr, addr_len, ifidx);

	read_lock_bh(&d->lock);
	for (e = d->l2tab[hash].first; e; e = e->next)
		if (!addreq(e, addr) && e->ifindex == ifidx) {
			spin_lock(&e->lock);
			if (atomic_read(&e->refcnt))
				goto found;
			spin_unlock(&e->lock);
			break;
		}
	read_unlock_bh(&d->lock);
	return;

 found:
	read_unlock(&d->lock);

	if (neigh != e->neigh)
		neigh_replace(e, neigh);

	if (e->state == L2T_STATE_RESOLVING) {
		if (neigh->nud_state & NUD_FAILED) {
			arpq = &e->arpq;
		} else if ((neigh->nud_state & (NUD_CONNECTED | NUD_STALE)) &&
			   !skb_queue_empty(&e->arpq)) {
			write_l2e(adap, e, 1);
		}
	} else {
		e->state = neigh->nud_state & NUD_CONNECTED ?
			L2T_STATE_VALID : L2T_STATE_STALE;
		if (memcmp(e->dmac, neigh->ha, sizeof(e->dmac)))
			write_l2e(adap, e, 0);
	}

	if (arpq)
		handle_failed_resolution(adap, e);
	spin_unlock_bh(&e->lock);
}
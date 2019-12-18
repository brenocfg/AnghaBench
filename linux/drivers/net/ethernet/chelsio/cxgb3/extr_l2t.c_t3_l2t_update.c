#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct t3cdev {int dummy; } ;
struct sk_buff_head {int dummy; } ;
struct neighbour {int nud_state; int /*<<< orphan*/  ha; TYPE_1__* dev; scalar_t__ primary_key; } ;
struct l2t_entry {scalar_t__ addr; int ifindex; scalar_t__ state; int /*<<< orphan*/  lock; int /*<<< orphan*/  dmac; int /*<<< orphan*/  arpq; struct neighbour* neigh; int /*<<< orphan*/  refcnt; struct l2t_entry* next; } ;
struct l2t_data {int /*<<< orphan*/  lock; TYPE_2__* l2tab; } ;
struct TYPE_4__ {struct l2t_entry* first; } ;
struct TYPE_3__ {int ifindex; } ;

/* Variables and functions */
 struct l2t_data* L2DATA (struct t3cdev*) ; 
 scalar_t__ L2T_STATE_RESOLVING ; 
 scalar_t__ L2T_STATE_STALE ; 
 scalar_t__ L2T_STATE_VALID ; 
 int NUD_CONNECTED ; 
 int NUD_FAILED ; 
 int NUD_STALE ; 
 int /*<<< orphan*/  __skb_queue_head_init (struct sk_buff_head*) ; 
 int arp_hash (scalar_t__,int,struct l2t_data*) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ether_addr_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  handle_failed_resolution (struct t3cdev*,struct sk_buff_head*) ; 
 int /*<<< orphan*/  neigh_replace (struct l2t_entry*,struct neighbour*) ; 
 int /*<<< orphan*/  read_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setup_l2e_send_pending (struct t3cdev*,int /*<<< orphan*/ *,struct l2t_entry*) ; 
 int /*<<< orphan*/  skb_queue_empty (struct sk_buff_head*) ; 
 int /*<<< orphan*/  skb_queue_splice_init (int /*<<< orphan*/ *,struct sk_buff_head*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void t3_l2t_update(struct t3cdev *dev, struct neighbour *neigh)
{
	struct sk_buff_head arpq;
	struct l2t_entry *e;
	struct l2t_data *d = L2DATA(dev);
	u32 addr = *(u32 *) neigh->primary_key;
	int ifidx = neigh->dev->ifindex;
	int hash = arp_hash(addr, ifidx, d);

	read_lock_bh(&d->lock);
	for (e = d->l2tab[hash].first; e; e = e->next)
		if (e->addr == addr && e->ifindex == ifidx) {
			spin_lock(&e->lock);
			goto found;
		}
	read_unlock_bh(&d->lock);
	return;

found:
	__skb_queue_head_init(&arpq);

	read_unlock(&d->lock);
	if (atomic_read(&e->refcnt)) {
		if (neigh != e->neigh)
			neigh_replace(e, neigh);

		if (e->state == L2T_STATE_RESOLVING) {
			if (neigh->nud_state & NUD_FAILED) {
				skb_queue_splice_init(&e->arpq, &arpq);
			} else if (neigh->nud_state & (NUD_CONNECTED|NUD_STALE))
				setup_l2e_send_pending(dev, NULL, e);
		} else {
			e->state = neigh->nud_state & NUD_CONNECTED ?
			    L2T_STATE_VALID : L2T_STATE_STALE;
			if (!ether_addr_equal(e->dmac, neigh->ha))
				setup_l2e_send_pending(dev, NULL, e);
		}
	}
	spin_unlock_bh(&e->lock);

	if (!skb_queue_empty(&arpq))
		handle_failed_resolution(dev, &arpq);
}
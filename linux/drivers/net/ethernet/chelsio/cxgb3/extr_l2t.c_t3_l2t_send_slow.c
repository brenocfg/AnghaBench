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
struct t3cdev {int dummy; } ;
struct sk_buff {int dummy; } ;
struct l2t_entry {int state; int /*<<< orphan*/  lock; int /*<<< orphan*/  arpq; int /*<<< orphan*/  neigh; } ;
struct cpl_l2t_write_req {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
#define  L2T_STATE_RESOLVING 130 
#define  L2T_STATE_STALE 129 
#define  L2T_STATE_VALID 128 
 int /*<<< orphan*/  __kfree_skb (struct sk_buff*) ; 
 struct sk_buff* alloc_skb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arpq_enqueue (struct l2t_entry*,struct sk_buff*) ; 
 int cxgb3_ofld_send (struct t3cdev*,struct sk_buff*) ; 
 int /*<<< orphan*/  neigh_event_send (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setup_l2e_send_pending (struct t3cdev*,struct sk_buff*,struct l2t_entry*) ; 
 int /*<<< orphan*/  skb_queue_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

int t3_l2t_send_slow(struct t3cdev *dev, struct sk_buff *skb,
		     struct l2t_entry *e)
{
again:
	switch (e->state) {
	case L2T_STATE_STALE:	/* entry is stale, kick off revalidation */
		neigh_event_send(e->neigh, NULL);
		spin_lock_bh(&e->lock);
		if (e->state == L2T_STATE_STALE)
			e->state = L2T_STATE_VALID;
		spin_unlock_bh(&e->lock);
		/* fall through */
	case L2T_STATE_VALID:	/* fast-path, send the packet on */
		return cxgb3_ofld_send(dev, skb);
	case L2T_STATE_RESOLVING:
		spin_lock_bh(&e->lock);
		if (e->state != L2T_STATE_RESOLVING) {
			/* ARP already completed */
			spin_unlock_bh(&e->lock);
			goto again;
		}
		arpq_enqueue(e, skb);
		spin_unlock_bh(&e->lock);

		/*
		 * Only the first packet added to the arpq should kick off
		 * resolution.  However, because the alloc_skb below can fail,
		 * we allow each packet added to the arpq to retry resolution
		 * as a way of recovering from transient memory exhaustion.
		 * A better way would be to use a work request to retry L2T
		 * entries when there's no memory.
		 */
		if (!neigh_event_send(e->neigh, NULL)) {
			skb = alloc_skb(sizeof(struct cpl_l2t_write_req),
					GFP_ATOMIC);
			if (!skb)
				break;

			spin_lock_bh(&e->lock);
			if (!skb_queue_empty(&e->arpq))
				setup_l2e_send_pending(dev, skb, e);
			else	/* we lost the race */
				__kfree_skb(skb);
			spin_unlock_bh(&e->lock);
		}
	}
	return 0;
}
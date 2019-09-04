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
struct sk_buff {int dummy; } ;
struct net_device {int dummy; } ;
struct l2t_entry {int state; int /*<<< orphan*/  lock; int /*<<< orphan*/  arpq; int /*<<< orphan*/  neigh; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
#define  L2T_STATE_RESOLVING 131 
#define  L2T_STATE_STALE 130 
#define  L2T_STATE_SYNC_WRITE 129 
#define  L2T_STATE_VALID 128 
 int /*<<< orphan*/  arpq_enqueue (struct l2t_entry*,struct sk_buff*) ; 
 int /*<<< orphan*/  neigh_event_send (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct adapter* netdev2adap (struct net_device*) ; 
 int /*<<< orphan*/  skb_queue_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int t4_ofld_send (struct adapter*,struct sk_buff*) ; 
 int /*<<< orphan*/  write_l2e (struct adapter*,struct l2t_entry*,int) ; 

int cxgb4_l2t_send(struct net_device *dev, struct sk_buff *skb,
		   struct l2t_entry *e)
{
	struct adapter *adap = netdev2adap(dev);

again:
	switch (e->state) {
	case L2T_STATE_STALE:     /* entry is stale, kick off revalidation */
		neigh_event_send(e->neigh, NULL);
		spin_lock_bh(&e->lock);
		if (e->state == L2T_STATE_STALE)
			e->state = L2T_STATE_VALID;
		spin_unlock_bh(&e->lock);
		/* fall through */
	case L2T_STATE_VALID:     /* fast-path, send the packet on */
		return t4_ofld_send(adap, skb);
	case L2T_STATE_RESOLVING:
	case L2T_STATE_SYNC_WRITE:
		spin_lock_bh(&e->lock);
		if (e->state != L2T_STATE_SYNC_WRITE &&
		    e->state != L2T_STATE_RESOLVING) {
			spin_unlock_bh(&e->lock);
			goto again;
		}
		arpq_enqueue(e, skb);
		spin_unlock_bh(&e->lock);

		if (e->state == L2T_STATE_RESOLVING &&
		    !neigh_event_send(e->neigh, NULL)) {
			spin_lock_bh(&e->lock);
			if (e->state == L2T_STATE_RESOLVING &&
			    !skb_queue_empty(&e->arpq))
				write_l2e(adap, e, 1);
			spin_unlock_bh(&e->lock);
		}
	}
	return 0;
}
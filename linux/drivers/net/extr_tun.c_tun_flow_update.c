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
typedef  scalar_t__ u16 ;
struct tun_struct {unsigned long ageing_time; scalar_t__ flow_count; int /*<<< orphan*/  lock; int /*<<< orphan*/  flow_gc_timer; struct hlist_head* flows; } ;
struct tun_flow_entry {scalar_t__ updated; int /*<<< orphan*/  rps_rxhash; int /*<<< orphan*/  queue_index; } ;
struct tun_file {scalar_t__ queue_index; } ;
struct hlist_head {int dummy; } ;

/* Variables and functions */
 scalar_t__ MAX_TAP_FLOWS ; 
 scalar_t__ READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ jiffies ; 
 scalar_t__ likely (struct tun_flow_entry*) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  round_jiffies_up (scalar_t__) ; 
 int /*<<< orphan*/  sock_rps_record_flow_hash (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_pending (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tun_flow_create (struct tun_struct*,struct hlist_head*,int /*<<< orphan*/ ,scalar_t__) ; 
 struct tun_flow_entry* tun_flow_find (struct hlist_head*,int /*<<< orphan*/ ) ; 
 size_t tun_hashfn (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tun_flow_update(struct tun_struct *tun, u32 rxhash,
			    struct tun_file *tfile)
{
	struct hlist_head *head;
	struct tun_flow_entry *e;
	unsigned long delay = tun->ageing_time;
	u16 queue_index = tfile->queue_index;

	head = &tun->flows[tun_hashfn(rxhash)];

	rcu_read_lock();

	e = tun_flow_find(head, rxhash);
	if (likely(e)) {
		/* TODO: keep queueing to old queue until it's empty? */
		if (READ_ONCE(e->queue_index) != queue_index)
			WRITE_ONCE(e->queue_index, queue_index);
		if (e->updated != jiffies)
			e->updated = jiffies;
		sock_rps_record_flow_hash(e->rps_rxhash);
	} else {
		spin_lock_bh(&tun->lock);
		if (!tun_flow_find(head, rxhash) &&
		    tun->flow_count < MAX_TAP_FLOWS)
			tun_flow_create(tun, head, rxhash, queue_index);

		if (!timer_pending(&tun->flow_gc_timer))
			mod_timer(&tun->flow_gc_timer,
				  round_jiffies_up(jiffies + delay));
		spin_unlock_bh(&tun->lock);
	}

	rcu_read_unlock();
}
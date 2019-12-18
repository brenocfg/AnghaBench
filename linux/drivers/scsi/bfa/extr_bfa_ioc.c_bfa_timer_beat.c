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
struct list_head {int dummy; } ;
struct bfa_timer_s {scalar_t__ timeout; int /*<<< orphan*/  arg; int /*<<< orphan*/  (* timercb ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  qe; } ;
struct bfa_timer_mod_s {struct list_head timer_q; } ;

/* Variables and functions */
 scalar_t__ BFA_TIMER_FREQ ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (struct list_head*) ; 
 int /*<<< orphan*/  bfa_q_deq (struct list_head*,struct bfa_timer_s**) ; 
 struct list_head* bfa_q_next (struct list_head*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,struct list_head*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (struct list_head*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

void
bfa_timer_beat(struct bfa_timer_mod_s *mod)
{
	struct list_head *qh = &mod->timer_q;
	struct list_head *qe, *qe_next;
	struct bfa_timer_s *elem;
	struct list_head timedout_q;

	INIT_LIST_HEAD(&timedout_q);

	qe = bfa_q_next(qh);

	while (qe != qh) {
		qe_next = bfa_q_next(qe);

		elem = (struct bfa_timer_s *) qe;
		if (elem->timeout <= BFA_TIMER_FREQ) {
			elem->timeout = 0;
			list_del(&elem->qe);
			list_add_tail(&elem->qe, &timedout_q);
		} else {
			elem->timeout -= BFA_TIMER_FREQ;
		}

		qe = qe_next;	/* go to next elem */
	}

	/*
	 * Pop all the timeout entries
	 */
	while (!list_empty(&timedout_q)) {
		bfa_q_deq(&timedout_q, &elem);
		elem->timercb(elem->arg);
	}
}
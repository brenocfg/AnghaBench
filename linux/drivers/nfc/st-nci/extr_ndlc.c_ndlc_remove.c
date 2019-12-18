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
struct llt_ndlc {int t2_active; int t1_active; int /*<<< orphan*/  send_q; int /*<<< orphan*/  rcv_q; int /*<<< orphan*/  t2_timer; int /*<<< orphan*/  t1_timer; int /*<<< orphan*/  ndev; } ;

/* Variables and functions */
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_purge (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  st_nci_remove (int /*<<< orphan*/ ) ; 

void ndlc_remove(struct llt_ndlc *ndlc)
{
	st_nci_remove(ndlc->ndev);

	/* cancel timers */
	del_timer_sync(&ndlc->t1_timer);
	del_timer_sync(&ndlc->t2_timer);
	ndlc->t2_active = false;
	ndlc->t1_active = false;

	skb_queue_purge(&ndlc->rcv_q);
	skb_queue_purge(&ndlc->send_q);
}
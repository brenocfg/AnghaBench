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
struct throtl_service_queue {scalar_t__* nr_queued; } ;
struct throtl_grp {struct throtl_service_queue service_queue; int /*<<< orphan*/  disptime; } ;

/* Variables and functions */
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  tg_update_disptime (struct throtl_grp*) ; 
 int /*<<< orphan*/  throtl_dequeue_tg (struct throtl_grp*) ; 
 scalar_t__ throtl_dispatch_tg (struct throtl_grp*) ; 
 unsigned int throtl_quantum ; 
 struct throtl_grp* throtl_rb_first (struct throtl_service_queue*) ; 
 scalar_t__ time_before (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int throtl_select_dispatch(struct throtl_service_queue *parent_sq)
{
	unsigned int nr_disp = 0;

	while (1) {
		struct throtl_grp *tg = throtl_rb_first(parent_sq);
		struct throtl_service_queue *sq;

		if (!tg)
			break;

		if (time_before(jiffies, tg->disptime))
			break;

		throtl_dequeue_tg(tg);

		nr_disp += throtl_dispatch_tg(tg);

		sq = &tg->service_queue;
		if (sq->nr_queued[0] || sq->nr_queued[1])
			tg_update_disptime(tg);

		if (nr_disp >= throtl_quantum)
			break;
	}

	return nr_disp;
}
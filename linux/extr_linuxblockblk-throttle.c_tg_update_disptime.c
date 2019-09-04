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
struct throtl_service_queue {int /*<<< orphan*/ * queued; } ;
struct throtl_grp {unsigned long disptime; int /*<<< orphan*/  flags; struct throtl_service_queue service_queue; } ;
struct bio {int dummy; } ;

/* Variables and functions */
 size_t READ ; 
 int /*<<< orphan*/  THROTL_TG_WAS_EMPTY ; 
 size_t WRITE ; 
 unsigned long jiffies ; 
 unsigned long min (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  tg_may_dispatch (struct throtl_grp*,struct bio*,unsigned long*) ; 
 int /*<<< orphan*/  throtl_dequeue_tg (struct throtl_grp*) ; 
 int /*<<< orphan*/  throtl_enqueue_tg (struct throtl_grp*) ; 
 struct bio* throtl_peek_queued (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void tg_update_disptime(struct throtl_grp *tg)
{
	struct throtl_service_queue *sq = &tg->service_queue;
	unsigned long read_wait = -1, write_wait = -1, min_wait = -1, disptime;
	struct bio *bio;

	bio = throtl_peek_queued(&sq->queued[READ]);
	if (bio)
		tg_may_dispatch(tg, bio, &read_wait);

	bio = throtl_peek_queued(&sq->queued[WRITE]);
	if (bio)
		tg_may_dispatch(tg, bio, &write_wait);

	min_wait = min(read_wait, write_wait);
	disptime = jiffies + min_wait;

	/* Update dispatch time */
	throtl_dequeue_tg(tg);
	tg->disptime = disptime;
	throtl_enqueue_tg(tg);

	/* see throtl_add_bio_tg() */
	tg->flags &= ~THROTL_TG_WAS_EMPTY;
}
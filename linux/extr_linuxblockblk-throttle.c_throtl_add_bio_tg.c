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
struct throtl_service_queue {int /*<<< orphan*/ * nr_queued; int /*<<< orphan*/ * queued; } ;
struct throtl_qnode {int dummy; } ;
struct throtl_grp {int /*<<< orphan*/  flags; struct throtl_qnode* qnode_on_self; struct throtl_service_queue service_queue; } ;
struct bio {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  THROTL_TG_WAS_EMPTY ; 
 int bio_data_dir (struct bio*) ; 
 int /*<<< orphan*/  throtl_enqueue_tg (struct throtl_grp*) ; 
 int /*<<< orphan*/  throtl_qnode_add_bio (struct bio*,struct throtl_qnode*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void throtl_add_bio_tg(struct bio *bio, struct throtl_qnode *qn,
			      struct throtl_grp *tg)
{
	struct throtl_service_queue *sq = &tg->service_queue;
	bool rw = bio_data_dir(bio);

	if (!qn)
		qn = &tg->qnode_on_self[rw];

	/*
	 * If @tg doesn't currently have any bios queued in the same
	 * direction, queueing @bio can change when @tg should be
	 * dispatched.  Mark that @tg was empty.  This is automatically
	 * cleaered on the next tg_update_disptime().
	 */
	if (!sq->nr_queued[rw])
		tg->flags |= THROTL_TG_WAS_EMPTY;

	throtl_qnode_add_bio(bio, qn, &sq->queued[rw]);

	sq->nr_queued[rw]++;
	throtl_enqueue_tg(tg);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct throtl_service_queue {int /*<<< orphan*/ * queued; int /*<<< orphan*/ * nr_queued; struct throtl_service_queue* parent_sq; } ;
struct throtl_grp {TYPE_1__* td; int /*<<< orphan*/ * qnode_on_parent; struct throtl_service_queue service_queue; } ;
struct bio {int dummy; } ;
struct TYPE_2__ {scalar_t__* nr_queued; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  blkg_put (int /*<<< orphan*/ ) ; 
 struct throtl_grp* sq_to_tg (struct throtl_service_queue*) ; 
 int /*<<< orphan*/  start_parent_slice_with_credit (struct throtl_grp*,struct throtl_grp*,int) ; 
 int /*<<< orphan*/  tg_to_blkg (struct throtl_grp*) ; 
 int /*<<< orphan*/  throtl_add_bio_tg (struct bio*,int /*<<< orphan*/ *,struct throtl_grp*) ; 
 int /*<<< orphan*/  throtl_charge_bio (struct throtl_grp*,struct bio*) ; 
 struct bio* throtl_pop_queued (int /*<<< orphan*/ *,struct throtl_grp**) ; 
 int /*<<< orphan*/  throtl_qnode_add_bio (struct bio*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  throtl_trim_slice (struct throtl_grp*,int) ; 

__attribute__((used)) static void tg_dispatch_one_bio(struct throtl_grp *tg, bool rw)
{
	struct throtl_service_queue *sq = &tg->service_queue;
	struct throtl_service_queue *parent_sq = sq->parent_sq;
	struct throtl_grp *parent_tg = sq_to_tg(parent_sq);
	struct throtl_grp *tg_to_put = NULL;
	struct bio *bio;

	/*
	 * @bio is being transferred from @tg to @parent_sq.  Popping a bio
	 * from @tg may put its reference and @parent_sq might end up
	 * getting released prematurely.  Remember the tg to put and put it
	 * after @bio is transferred to @parent_sq.
	 */
	bio = throtl_pop_queued(&sq->queued[rw], &tg_to_put);
	sq->nr_queued[rw]--;

	throtl_charge_bio(tg, bio);

	/*
	 * If our parent is another tg, we just need to transfer @bio to
	 * the parent using throtl_add_bio_tg().  If our parent is
	 * @td->service_queue, @bio is ready to be issued.  Put it on its
	 * bio_lists[] and decrease total number queued.  The caller is
	 * responsible for issuing these bios.
	 */
	if (parent_tg) {
		throtl_add_bio_tg(bio, &tg->qnode_on_parent[rw], parent_tg);
		start_parent_slice_with_credit(tg, parent_tg, rw);
	} else {
		throtl_qnode_add_bio(bio, &tg->qnode_on_parent[rw],
				     &parent_sq->queued[rw]);
		BUG_ON(tg->td->nr_queued[rw] <= 0);
		tg->td->nr_queued[rw]--;
	}

	throtl_trim_slice(tg, rw);

	if (tg_to_put)
		blkg_put(tg_to_blkg(tg_to_put));
}
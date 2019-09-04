#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct ib_cq {TYPE_1__* uobject; } ;
struct c4iw_ucontext {int /*<<< orphan*/  uctx; } ;
struct TYPE_8__ {TYPE_2__* rdev; int /*<<< orphan*/  cqid; } ;
struct c4iw_cq {int /*<<< orphan*/  wr_waitp; int /*<<< orphan*/  destroy_skb; TYPE_4__ cq; TYPE_3__* rhp; int /*<<< orphan*/  refcnt; int /*<<< orphan*/  wait; } ;
struct TYPE_7__ {int /*<<< orphan*/  rdev; int /*<<< orphan*/  cqidr; } ;
struct TYPE_6__ {int /*<<< orphan*/  uctx; } ;
struct TYPE_5__ {int /*<<< orphan*/  context; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  c4iw_put_wr_wait (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  destroy_cq (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct c4iw_cq*) ; 
 int /*<<< orphan*/  pr_debug (char*,struct ib_cq*) ; 
 int /*<<< orphan*/  remove_handle (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct c4iw_cq* to_c4iw_cq (struct ib_cq*) ; 
 struct c4iw_ucontext* to_c4iw_ucontext (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

int c4iw_destroy_cq(struct ib_cq *ib_cq)
{
	struct c4iw_cq *chp;
	struct c4iw_ucontext *ucontext;

	pr_debug("ib_cq %p\n", ib_cq);
	chp = to_c4iw_cq(ib_cq);

	remove_handle(chp->rhp, &chp->rhp->cqidr, chp->cq.cqid);
	atomic_dec(&chp->refcnt);
	wait_event(chp->wait, !atomic_read(&chp->refcnt));

	ucontext = ib_cq->uobject ? to_c4iw_ucontext(ib_cq->uobject->context)
				  : NULL;
	destroy_cq(&chp->rhp->rdev, &chp->cq,
		   ucontext ? &ucontext->uctx : &chp->cq.rdev->uctx,
		   chp->destroy_skb, chp->wr_waitp);
	c4iw_put_wr_wait(chp->wr_waitp);
	kfree(chp);
	return 0;
}
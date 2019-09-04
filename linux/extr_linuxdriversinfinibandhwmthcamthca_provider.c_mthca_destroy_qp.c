#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct ib_qp {int /*<<< orphan*/  device; TYPE_3__* uobject; } ;
struct TYPE_8__ {int /*<<< orphan*/  db_index; } ;
struct TYPE_7__ {int /*<<< orphan*/  db_index; } ;
struct TYPE_11__ {TYPE_2__ rq; TYPE_1__ sq; } ;
struct TYPE_10__ {int /*<<< orphan*/  db_tab; int /*<<< orphan*/  uar; } ;
struct TYPE_9__ {int /*<<< orphan*/  context; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct ib_qp*) ; 
 int /*<<< orphan*/  mthca_free_qp (int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  mthca_unmap_user_db (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_mdev (int /*<<< orphan*/ ) ; 
 TYPE_5__* to_mqp (struct ib_qp*) ; 
 TYPE_4__* to_mucontext (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mthca_destroy_qp(struct ib_qp *qp)
{
	if (qp->uobject) {
		mthca_unmap_user_db(to_mdev(qp->device),
				    &to_mucontext(qp->uobject->context)->uar,
				    to_mucontext(qp->uobject->context)->db_tab,
				    to_mqp(qp)->sq.db_index);
		mthca_unmap_user_db(to_mdev(qp->device),
				    &to_mucontext(qp->uobject->context)->uar,
				    to_mucontext(qp->uobject->context)->db_tab,
				    to_mqp(qp)->rq.db_index);
	}
	mthca_free_qp(to_mdev(qp->device), to_mqp(qp));
	kfree(qp);
	return 0;
}
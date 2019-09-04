#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct ib_cq {int /*<<< orphan*/  device; TYPE_1__* uobject; } ;
struct TYPE_7__ {int /*<<< orphan*/  set_ci_db_index; int /*<<< orphan*/  arm_db_index; } ;
struct TYPE_6__ {int /*<<< orphan*/  db_tab; int /*<<< orphan*/  uar; } ;
struct TYPE_5__ {int /*<<< orphan*/  context; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct ib_cq*) ; 
 int /*<<< orphan*/  mthca_free_cq (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  mthca_unmap_user_db (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* to_mcq (struct ib_cq*) ; 
 int /*<<< orphan*/  to_mdev (int /*<<< orphan*/ ) ; 
 TYPE_2__* to_mucontext (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mthca_destroy_cq(struct ib_cq *cq)
{
	if (cq->uobject) {
		mthca_unmap_user_db(to_mdev(cq->device),
				    &to_mucontext(cq->uobject->context)->uar,
				    to_mucontext(cq->uobject->context)->db_tab,
				    to_mcq(cq)->arm_db_index);
		mthca_unmap_user_db(to_mdev(cq->device),
				    &to_mucontext(cq->uobject->context)->uar,
				    to_mucontext(cq->uobject->context)->db_tab,
				    to_mcq(cq)->set_ci_db_index);
	}
	mthca_free_cq(to_mdev(cq->device), to_mcq(cq));
	kfree(cq);

	return 0;
}
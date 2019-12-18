#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ db_index; int /*<<< orphan*/  db; } ;
struct TYPE_3__ {scalar_t__ db_index; int /*<<< orphan*/  db; } ;
struct mthca_qp {TYPE_2__ rq; TYPE_1__ sq; int /*<<< orphan*/  qpn; } ;
struct mthca_dev {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  MTHCA_DB_TYPE_RQ ; 
 int /*<<< orphan*/  MTHCA_DB_TYPE_SQ ; 
 void* mthca_alloc_db (struct mthca_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mthca_free_db (struct mthca_dev*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ mthca_is_memfree (struct mthca_dev*) ; 

__attribute__((used)) static int mthca_alloc_memfree(struct mthca_dev *dev,
			       struct mthca_qp *qp)
{
	if (mthca_is_memfree(dev)) {
		qp->rq.db_index = mthca_alloc_db(dev, MTHCA_DB_TYPE_RQ,
						 qp->qpn, &qp->rq.db);
		if (qp->rq.db_index < 0)
			return -ENOMEM;

		qp->sq.db_index = mthca_alloc_db(dev, MTHCA_DB_TYPE_SQ,
						 qp->qpn, &qp->sq.db);
		if (qp->sq.db_index < 0) {
			mthca_free_db(dev, MTHCA_DB_TYPE_RQ, qp->rq.db_index);
			return -ENOMEM;
		}
	}

	return 0;
}
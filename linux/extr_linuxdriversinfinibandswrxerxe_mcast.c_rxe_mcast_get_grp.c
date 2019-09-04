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
typedef  union ib_gid {int dummy; } ib_gid ;
struct rxe_mc_grp {struct rxe_dev* rxe; int /*<<< orphan*/  mcg_lock; int /*<<< orphan*/  qp_list; } ;
struct TYPE_2__ {scalar_t__ max_mcast_qp_attach; } ;
struct rxe_dev {int /*<<< orphan*/  mc_grp_pool; TYPE_1__ attr; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rxe_add_key (struct rxe_mc_grp*,union ib_gid*) ; 
 struct rxe_mc_grp* rxe_alloc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rxe_drop_ref (struct rxe_mc_grp*) ; 
 int rxe_mcast_add (struct rxe_dev*,union ib_gid*) ; 
 struct rxe_mc_grp* rxe_pool_get_key (int /*<<< orphan*/ *,union ib_gid*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int rxe_mcast_get_grp(struct rxe_dev *rxe, union ib_gid *mgid,
		      struct rxe_mc_grp **grp_p)
{
	int err;
	struct rxe_mc_grp *grp;

	if (rxe->attr.max_mcast_qp_attach == 0) {
		err = -EINVAL;
		goto err1;
	}

	grp = rxe_pool_get_key(&rxe->mc_grp_pool, mgid);
	if (grp)
		goto done;

	grp = rxe_alloc(&rxe->mc_grp_pool);
	if (!grp) {
		err = -ENOMEM;
		goto err1;
	}

	INIT_LIST_HEAD(&grp->qp_list);
	spin_lock_init(&grp->mcg_lock);
	grp->rxe = rxe;

	rxe_add_key(grp, mgid);

	err = rxe_mcast_add(rxe, mgid);
	if (err)
		goto err2;

done:
	*grp_p = grp;
	return 0;

err2:
	rxe_drop_ref(grp);
err1:
	return err;
}
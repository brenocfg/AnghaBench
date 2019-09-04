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
typedef  union ib_gid {int dummy; } ib_gid ;
typedef  int /*<<< orphan*/  u16 ;
struct rxe_qp {int dummy; } ;
struct rxe_mc_grp {int dummy; } ;
struct rxe_dev {int dummy; } ;
struct ib_qp {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  rxe_drop_ref (struct rxe_mc_grp*) ; 
 int rxe_mcast_add_grp_elem (struct rxe_dev*,struct rxe_qp*,struct rxe_mc_grp*) ; 
 int rxe_mcast_get_grp (struct rxe_dev*,union ib_gid*,struct rxe_mc_grp**) ; 
 struct rxe_dev* to_rdev (int /*<<< orphan*/ ) ; 
 struct rxe_qp* to_rqp (struct ib_qp*) ; 

__attribute__((used)) static int rxe_attach_mcast(struct ib_qp *ibqp, union ib_gid *mgid, u16 mlid)
{
	int err;
	struct rxe_dev *rxe = to_rdev(ibqp->device);
	struct rxe_qp *qp = to_rqp(ibqp);
	struct rxe_mc_grp *grp;

	/* takes a ref on grp if successful */
	err = rxe_mcast_get_grp(rxe, mgid, &grp);
	if (err)
		return err;

	err = rxe_mcast_add_grp_elem(rxe, qp, grp);

	rxe_drop_ref(grp);
	return err;
}
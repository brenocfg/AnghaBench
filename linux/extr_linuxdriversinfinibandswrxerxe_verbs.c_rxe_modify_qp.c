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
struct rxe_qp {int dummy; } ;
struct rxe_dev {int dummy; } ;
struct ib_udata {int dummy; } ;
struct ib_qp_attr {int dummy; } ;
struct ib_qp {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int rxe_qp_chk_attr (struct rxe_dev*,struct rxe_qp*,struct ib_qp_attr*,int) ; 
 int rxe_qp_from_attr (struct rxe_qp*,struct ib_qp_attr*,int,struct ib_udata*) ; 
 struct rxe_dev* to_rdev (int /*<<< orphan*/ ) ; 
 struct rxe_qp* to_rqp (struct ib_qp*) ; 

__attribute__((used)) static int rxe_modify_qp(struct ib_qp *ibqp, struct ib_qp_attr *attr,
			 int mask, struct ib_udata *udata)
{
	int err;
	struct rxe_dev *rxe = to_rdev(ibqp->device);
	struct rxe_qp *qp = to_rqp(ibqp);

	err = rxe_qp_chk_attr(rxe, qp, attr, mask);
	if (err)
		goto err1;

	err = rxe_qp_from_attr(qp, attr, mask, udata);
	if (err)
		goto err1;

	return 0;

err1:
	return err;
}
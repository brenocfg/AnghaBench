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
typedef  int /*<<< orphan*/  ucmd ;
struct rxe_srq {int dummy; } ;
struct rxe_modify_srq_cmd {int dummy; } ;
struct rxe_dev {int dummy; } ;
struct ib_udata {int inlen; } ;
struct ib_srq_attr {int dummy; } ;
struct ib_srq {int /*<<< orphan*/  device; } ;
typedef  enum ib_srq_attr_mask { ____Placeholder_ib_srq_attr_mask } ib_srq_attr_mask ;

/* Variables and functions */
 int EINVAL ; 
 int ib_copy_from_udata (struct rxe_modify_srq_cmd*,struct ib_udata*,int) ; 
 int rxe_srq_chk_attr (struct rxe_dev*,struct rxe_srq*,struct ib_srq_attr*,int) ; 
 int rxe_srq_from_attr (struct rxe_dev*,struct rxe_srq*,struct ib_srq_attr*,int,struct rxe_modify_srq_cmd*,struct ib_udata*) ; 
 struct rxe_dev* to_rdev (int /*<<< orphan*/ ) ; 
 struct rxe_srq* to_rsrq (struct ib_srq*) ; 

__attribute__((used)) static int rxe_modify_srq(struct ib_srq *ibsrq, struct ib_srq_attr *attr,
			  enum ib_srq_attr_mask mask,
			  struct ib_udata *udata)
{
	int err;
	struct rxe_srq *srq = to_rsrq(ibsrq);
	struct rxe_dev *rxe = to_rdev(ibsrq->device);
	struct rxe_modify_srq_cmd ucmd = {};

	if (udata) {
		if (udata->inlen < sizeof(ucmd))
			return -EINVAL;

		err = ib_copy_from_udata(&ucmd, udata, sizeof(ucmd));
		if (err)
			return err;
	}

	err = rxe_srq_chk_attr(rxe, srq, attr, mask);
	if (err)
		goto err1;

	err = rxe_srq_from_attr(rxe, srq, attr, mask, &ucmd, udata);
	if (err)
		goto err1;

	return 0;

err1:
	return err;
}
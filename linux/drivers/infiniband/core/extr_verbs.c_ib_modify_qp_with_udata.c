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
struct ib_udata {int dummy; } ;
struct ib_qp_attr {int dummy; } ;
struct ib_qp {int /*<<< orphan*/  real_qp; } ;

/* Variables and functions */
 int _ib_modify_qp (int /*<<< orphan*/ ,struct ib_qp_attr*,int,struct ib_udata*) ; 

int ib_modify_qp_with_udata(struct ib_qp *ib_qp, struct ib_qp_attr *attr,
			    int attr_mask, struct ib_udata *udata)
{
	return _ib_modify_qp(ib_qp->real_qp, attr, attr_mask, udata);
}
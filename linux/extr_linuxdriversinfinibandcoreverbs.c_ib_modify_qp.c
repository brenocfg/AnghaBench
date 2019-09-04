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
struct ib_qp_attr {int dummy; } ;
struct ib_qp {int /*<<< orphan*/  real_qp; } ;

/* Variables and functions */
 int _ib_modify_qp (int /*<<< orphan*/ ,struct ib_qp_attr*,int,int /*<<< orphan*/ *) ; 

int ib_modify_qp(struct ib_qp *qp,
		 struct ib_qp_attr *qp_attr,
		 int qp_attr_mask)
{
	return _ib_modify_qp(qp->real_qp, qp_attr, qp_attr_mask, NULL);
}
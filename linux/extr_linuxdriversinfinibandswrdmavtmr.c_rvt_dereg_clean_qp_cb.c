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
typedef  scalar_t__ u64 ;
struct TYPE_2__ {scalar_t__ pd; } ;
struct rvt_qp {TYPE_1__ ibqp; } ;
struct rvt_mregion {scalar_t__ pd; int /*<<< orphan*/  lkey; } ;

/* Variables and functions */
 int /*<<< orphan*/  rvt_qp_mr_clean (struct rvt_qp*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rvt_dereg_clean_qp_cb(struct rvt_qp *qp, u64 v)
{
	struct rvt_mregion *mr = (struct rvt_mregion *)v;

	/* skip PDs that are not ours */
	if (mr->pd != qp->ibqp.pd)
		return;
	rvt_qp_mr_clean(qp, mr->lkey);
}
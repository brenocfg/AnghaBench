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
struct rvt_qp {int dummy; } ;
struct rvt_mcast_qp {struct rvt_qp* qp; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct rvt_mcast_qp*) ; 
 int /*<<< orphan*/  rvt_put_qp (struct rvt_qp*) ; 

__attribute__((used)) static void rvt_mcast_qp_free(struct rvt_mcast_qp *mqp)
{
	struct rvt_qp *qp = mqp->qp;

	/* Notify hfi1_destroy_qp() if it is waiting. */
	rvt_put_qp(qp);

	kfree(mqp);
}
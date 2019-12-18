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
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct rvt_mcast_qp* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rvt_get_qp (struct rvt_qp*) ; 

__attribute__((used)) static struct rvt_mcast_qp *rvt_mcast_qp_alloc(struct rvt_qp *qp)
{
	struct rvt_mcast_qp *mqp;

	mqp = kmalloc(sizeof(*mqp), GFP_KERNEL);
	if (!mqp)
		goto bail;

	mqp->qp = qp;
	rvt_get_qp(qp);

bail:
	return mqp;
}
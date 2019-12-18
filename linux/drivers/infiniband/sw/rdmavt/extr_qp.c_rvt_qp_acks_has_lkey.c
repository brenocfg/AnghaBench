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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {int /*<<< orphan*/  device; } ;
struct rvt_qp {struct rvt_ack_entry* s_ack_queue; TYPE_1__ ibqp; } ;
struct rvt_dev_info {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  mr; } ;
struct rvt_ack_entry {TYPE_2__ rdma_sge; } ;

/* Variables and functions */
 struct rvt_dev_info* ib_to_rvt (int /*<<< orphan*/ ) ; 
 int rvt_max_atomic (struct rvt_dev_info*) ; 
 scalar_t__ rvt_mr_has_lkey (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool rvt_qp_acks_has_lkey(struct rvt_qp *qp, u32 lkey)
{
	int i;
	struct rvt_dev_info *rdi = ib_to_rvt(qp->ibqp.device);

	for (i = 0; qp->s_ack_queue && i < rvt_max_atomic(rdi); i++) {
		struct rvt_ack_entry *e = &qp->s_ack_queue[i];

		if (rvt_mr_has_lkey(e->rdma_sge.mr, lkey))
			return true;
	}
	return false;
}
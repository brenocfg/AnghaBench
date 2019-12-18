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
typedef  scalar_t__ u32 ;
struct TYPE_4__ {int /*<<< orphan*/  qp_num; } ;
struct rvt_qp {int s_avail; scalar_t__ s_head; int s_size; int /*<<< orphan*/  s_last; int /*<<< orphan*/  s_acked; int /*<<< orphan*/  s_cur; int /*<<< orphan*/  s_tail; TYPE_2__ ibqp; int /*<<< orphan*/  s_reserved_used; } ;
struct TYPE_3__ {scalar_t__ reserved_operations; } ;
struct rvt_dev_info {TYPE_1__ dparms; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ WARN_ON (int) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  rvt_pr_err (struct rvt_dev_info*,char*,int /*<<< orphan*/ ,int,int,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ smp_load_acquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_mb__before_atomic () ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline int rvt_qp_is_avail(
	struct rvt_qp *qp,
	struct rvt_dev_info *rdi,
	bool reserved_op)
{
	u32 slast;
	u32 avail;
	u32 reserved_used;

	/* see rvt_qp_wqe_unreserve() */
	smp_mb__before_atomic();
	if (unlikely(reserved_op)) {
		/* see rvt_qp_wqe_unreserve() */
		reserved_used = atomic_read(&qp->s_reserved_used);
		if (reserved_used >= rdi->dparms.reserved_operations)
			return -ENOMEM;
		return 0;
	}
	/* non-reserved operations */
	if (likely(qp->s_avail))
		return 0;
	/* See rvt_qp_complete_swqe() */
	slast = smp_load_acquire(&qp->s_last);
	if (qp->s_head >= slast)
		avail = qp->s_size - (qp->s_head - slast);
	else
		avail = slast - qp->s_head;

	reserved_used = atomic_read(&qp->s_reserved_used);
	avail =  avail - 1 -
		(rdi->dparms.reserved_operations - reserved_used);
	/* insure we don't assign a negative s_avail */
	if ((s32)avail <= 0)
		return -ENOMEM;
	qp->s_avail = avail;
	if (WARN_ON(qp->s_avail >
		    (qp->s_size - 1 - rdi->dparms.reserved_operations)))
		rvt_pr_err(rdi,
			   "More avail entries than QP RB size.\nQP: %u, size: %u, avail: %u\nhead: %u, tail: %u, cur: %u, acked: %u, last: %u",
			   qp->ibqp.qp_num, qp->s_size, qp->s_avail,
			   qp->s_head, qp->s_tail, qp->s_cur,
			   qp->s_acked, qp->s_last);
	return 0;
}
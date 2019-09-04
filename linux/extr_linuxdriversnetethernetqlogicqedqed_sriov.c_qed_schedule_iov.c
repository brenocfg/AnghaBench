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
struct qed_hwfn {int /*<<< orphan*/  iov_task; int /*<<< orphan*/  iov_wq; int /*<<< orphan*/  iov_task_flags; } ;
typedef  enum qed_iov_wq_flag { ____Placeholder_qed_iov_wq_flag } qed_iov_wq_flag ;

/* Variables and functions */
 int /*<<< orphan*/  DP_VERBOSE (struct qed_hwfn*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  QED_MSG_IOV ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_mb__after_atomic () ; 
 int /*<<< orphan*/  smp_mb__before_atomic () ; 

void qed_schedule_iov(struct qed_hwfn *hwfn, enum qed_iov_wq_flag flag)
{
	smp_mb__before_atomic();
	set_bit(flag, &hwfn->iov_task_flags);
	smp_mb__after_atomic();
	DP_VERBOSE(hwfn, QED_MSG_IOV, "Scheduling iov task [Flag: %d]\n", flag);
	queue_delayed_work(hwfn->iov_wq, &hwfn->iov_task, 0);
}
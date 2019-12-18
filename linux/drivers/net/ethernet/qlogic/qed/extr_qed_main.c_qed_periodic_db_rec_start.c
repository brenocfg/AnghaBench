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
struct qed_hwfn {int /*<<< orphan*/  slowpath_task_flags; int /*<<< orphan*/  periodic_db_rec_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  QED_PERIODIC_DB_REC_COUNT ; 
 int /*<<< orphan*/  QED_PERIODIC_DB_REC_INTERVAL ; 
 int /*<<< orphan*/  QED_SLOWPATH_PERIODIC_DB_REC ; 
 int /*<<< orphan*/  qed_slowpath_delayed_work (struct qed_hwfn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void qed_periodic_db_rec_start(struct qed_hwfn *p_hwfn)
{
	/* Reset periodic Doorbell Recovery counter */
	p_hwfn->periodic_db_rec_count = QED_PERIODIC_DB_REC_COUNT;

	/* Don't schedule periodic Doorbell Recovery if already scheduled */
	if (test_bit(QED_SLOWPATH_PERIODIC_DB_REC,
		     &p_hwfn->slowpath_task_flags))
		return;

	qed_slowpath_delayed_work(p_hwfn, QED_SLOWPATH_PERIODIC_DB_REC,
				  QED_PERIODIC_DB_REC_INTERVAL);
}
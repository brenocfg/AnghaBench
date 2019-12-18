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
struct TYPE_3__ {scalar_t__ db_recovery_counter; int /*<<< orphan*/  lock; int /*<<< orphan*/  list; } ;
struct qed_hwfn {TYPE_1__ db_recovery_info; TYPE_2__* cdev; } ;
struct TYPE_4__ {int /*<<< orphan*/  db_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_ERR (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  DP_VERBOSE (struct qed_hwfn*,int /*<<< orphan*/ ,char*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  QED_MSG_SPQ ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int qed_db_recovery_setup(struct qed_hwfn *p_hwfn)
{
	DP_VERBOSE(p_hwfn, QED_MSG_SPQ, "Setting up db recovery\n");

	/* Make sure db_size was set in cdev */
	if (!p_hwfn->cdev->db_size) {
		DP_ERR(p_hwfn->cdev, "db_size not set\n");
		return -EINVAL;
	}

	INIT_LIST_HEAD(&p_hwfn->db_recovery_info.list);
	spin_lock_init(&p_hwfn->db_recovery_info.lock);
	p_hwfn->db_recovery_info.db_recovery_counter = 0;

	return 0;
}
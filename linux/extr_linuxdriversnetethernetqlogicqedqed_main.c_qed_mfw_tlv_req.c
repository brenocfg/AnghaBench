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
struct qed_hwfn {int /*<<< orphan*/  slowpath_task; int /*<<< orphan*/  slowpath_wq; int /*<<< orphan*/  slowpath_task_flags; int /*<<< orphan*/  cdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_VERBOSE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NETIF_MSG_DRV ; 
 int /*<<< orphan*/  QED_SLOWPATH_MFW_TLV_REQ ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_mb__after_atomic () ; 
 int /*<<< orphan*/  smp_mb__before_atomic () ; 

int qed_mfw_tlv_req(struct qed_hwfn *hwfn)
{
	DP_VERBOSE(hwfn->cdev, NETIF_MSG_DRV,
		   "Scheduling slowpath task [Flag: %d]\n",
		   QED_SLOWPATH_MFW_TLV_REQ);
	smp_mb__before_atomic();
	set_bit(QED_SLOWPATH_MFW_TLV_REQ, &hwfn->slowpath_task_flags);
	smp_mb__after_atomic();
	queue_delayed_work(hwfn->slowpath_wq, &hwfn->slowpath_task, 0);

	return 0;
}
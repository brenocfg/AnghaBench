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
typedef  int /*<<< orphan*/  u32 ;
struct qed_ptt {int dummy; } ;
struct qed_hwfn {struct qed_dev* cdev; } ;
struct qed_dev {int recov_in_prog; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_NOTICE (struct qed_hwfn*,char*,...) ; 
 struct qed_hwfn* QED_LEADING_HWFN (struct qed_dev*) ; 
 int /*<<< orphan*/  qed_get_process_kill_counter (struct qed_hwfn*,struct qed_ptt*) ; 
 int /*<<< orphan*/  qed_int_igu_disable_int (struct qed_hwfn*,struct qed_ptt*) ; 
 int /*<<< orphan*/  qed_schedule_recovery_handler (struct qed_hwfn*) ; 

__attribute__((used)) static void qed_mcp_handle_process_kill(struct qed_hwfn *p_hwfn,
					struct qed_ptt *p_ptt)
{
	struct qed_dev *cdev = p_hwfn->cdev;
	u32 proc_kill_cnt;

	/* Prevent possible attentions/interrupts during the recovery handling
	 * and till its load phase, during which they will be re-enabled.
	 */
	qed_int_igu_disable_int(p_hwfn, p_ptt);

	DP_NOTICE(p_hwfn, "Received a process kill indication\n");

	/* The following operations should be done once, and thus in CMT mode
	 * are carried out by only the first HW function.
	 */
	if (p_hwfn != QED_LEADING_HWFN(cdev))
		return;

	if (cdev->recov_in_prog) {
		DP_NOTICE(p_hwfn,
			  "Ignoring the indication since a recovery process is already in progress\n");
		return;
	}

	cdev->recov_in_prog = true;

	proc_kill_cnt = qed_get_process_kill_counter(p_hwfn, p_ptt);
	DP_NOTICE(p_hwfn, "Process kill counter: %d\n", proc_kill_cnt);

	qed_schedule_recovery_handler(p_hwfn);
}
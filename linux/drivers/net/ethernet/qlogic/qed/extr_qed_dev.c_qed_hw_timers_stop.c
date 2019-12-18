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
typedef  int /*<<< orphan*/  u8 ;
struct qed_ptt {int dummy; } ;
struct qed_hwfn {int dummy; } ;
struct qed_dev {scalar_t__ recov_in_prog; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_NOTICE (struct qed_hwfn*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int QED_HW_STOP_RETRY_LIMIT ; 
 int /*<<< orphan*/  TM_REG_PF_ENABLE_CONN ; 
 int /*<<< orphan*/  TM_REG_PF_ENABLE_TASK ; 
 int /*<<< orphan*/  TM_REG_PF_SCAN_ACTIVE_CONN ; 
 int /*<<< orphan*/  TM_REG_PF_SCAN_ACTIVE_TASK ; 
 scalar_t__ qed_rd (struct qed_hwfn*,struct qed_ptt*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qed_wr (struct qed_hwfn*,struct qed_ptt*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void qed_hw_timers_stop(struct qed_dev *cdev,
			       struct qed_hwfn *p_hwfn, struct qed_ptt *p_ptt)
{
	int i;

	/* close timers */
	qed_wr(p_hwfn, p_ptt, TM_REG_PF_ENABLE_CONN, 0x0);
	qed_wr(p_hwfn, p_ptt, TM_REG_PF_ENABLE_TASK, 0x0);

	if (cdev->recov_in_prog)
		return;

	for (i = 0; i < QED_HW_STOP_RETRY_LIMIT; i++) {
		if ((!qed_rd(p_hwfn, p_ptt,
			     TM_REG_PF_SCAN_ACTIVE_CONN)) &&
		    (!qed_rd(p_hwfn, p_ptt, TM_REG_PF_SCAN_ACTIVE_TASK)))
			break;

		/* Dependent on number of connection/tasks, possibly
		 * 1ms sleep is required between polls
		 */
		usleep_range(1000, 2000);
	}

	if (i < QED_HW_STOP_RETRY_LIMIT)
		return;

	DP_NOTICE(p_hwfn,
		  "Timers linear scans are not over [Connection %02x Tasks %02x]\n",
		  (u8)qed_rd(p_hwfn, p_ptt, TM_REG_PF_SCAN_ACTIVE_CONN),
		  (u8)qed_rd(p_hwfn, p_ptt, TM_REG_PF_SCAN_ACTIVE_TASK));
}
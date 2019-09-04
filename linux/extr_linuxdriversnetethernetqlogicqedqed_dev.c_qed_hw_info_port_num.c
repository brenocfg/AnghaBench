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
struct qed_ptt {int dummy; } ;
struct qed_hwfn {int /*<<< orphan*/  cdev; } ;

/* Variables and functions */
 scalar_t__ QED_IS_BB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qed_hw_info_port_num_ah (struct qed_hwfn*,struct qed_ptt*) ; 
 int /*<<< orphan*/  qed_hw_info_port_num_bb (struct qed_hwfn*,struct qed_ptt*) ; 

__attribute__((used)) static void qed_hw_info_port_num(struct qed_hwfn *p_hwfn, struct qed_ptt *p_ptt)
{
	if (QED_IS_BB(p_hwfn->cdev))
		qed_hw_info_port_num_bb(p_hwfn, p_ptt);
	else
		qed_hw_info_port_num_ah(p_hwfn, p_ptt);
}
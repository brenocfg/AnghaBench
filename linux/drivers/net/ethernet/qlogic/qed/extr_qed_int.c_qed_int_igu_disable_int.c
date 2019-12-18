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
struct qed_hwfn {int /*<<< orphan*/  cdev; scalar_t__ b_int_enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  IGU_REG_PF_CONFIGURATION ; 
 scalar_t__ IS_VF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qed_wr (struct qed_hwfn*,struct qed_ptt*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void qed_int_igu_disable_int(struct qed_hwfn *p_hwfn, struct qed_ptt *p_ptt)
{
	p_hwfn->b_int_enabled = 0;

	if (IS_VF(p_hwfn->cdev))
		return;

	qed_wr(p_hwfn, p_ptt, IGU_REG_PF_CONFIGURATION, 0);
}
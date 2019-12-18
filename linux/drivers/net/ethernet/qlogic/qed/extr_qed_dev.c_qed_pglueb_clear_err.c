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
struct qed_hwfn {int /*<<< orphan*/  abs_pf_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PGLUE_B_REG_WAS_ERROR_PF_31_0_CLR ; 
 int /*<<< orphan*/  qed_wr (struct qed_hwfn*,struct qed_ptt*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qed_pglueb_clear_err(struct qed_hwfn *p_hwfn, struct qed_ptt *p_ptt)
{
	qed_wr(p_hwfn, p_ptt, PGLUE_B_REG_WAS_ERROR_PF_31_0_CLR,
	       BIT(p_hwfn->abs_pf_id));
}
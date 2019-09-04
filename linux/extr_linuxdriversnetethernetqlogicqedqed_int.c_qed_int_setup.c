#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct qed_ptt {int dummy; } ;
struct qed_hwfn {TYPE_1__* p_sp_sb; } ;
struct TYPE_2__ {int /*<<< orphan*/  sb_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  qed_int_sb_attn_setup (struct qed_hwfn*,struct qed_ptt*) ; 
 int /*<<< orphan*/  qed_int_sb_setup (struct qed_hwfn*,struct qed_ptt*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qed_int_sp_dpc_setup (struct qed_hwfn*) ; 

void qed_int_setup(struct qed_hwfn *p_hwfn, struct qed_ptt *p_ptt)
{
	qed_int_sb_setup(p_hwfn, p_ptt, &p_hwfn->p_sp_sb->sb_info);
	qed_int_sb_attn_setup(p_hwfn, p_ptt);
	qed_int_sp_dpc_setup(p_hwfn);
}
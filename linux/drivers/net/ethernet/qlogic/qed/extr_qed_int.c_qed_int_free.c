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
struct qed_hwfn {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  qed_int_sb_attn_free (struct qed_hwfn*) ; 
 int /*<<< orphan*/  qed_int_sp_dpc_free (struct qed_hwfn*) ; 
 int /*<<< orphan*/  qed_int_sp_sb_free (struct qed_hwfn*) ; 

void qed_int_free(struct qed_hwfn *p_hwfn)
{
	qed_int_sp_sb_free(p_hwfn);
	qed_int_sb_attn_free(p_hwfn);
	qed_int_sp_dpc_free(p_hwfn);
}
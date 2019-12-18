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
struct qed_hwfn {int dummy; } ;

/* Variables and functions */
 int qed_int_sb_attn_alloc (struct qed_hwfn*,struct qed_ptt*) ; 
 int qed_int_sp_dpc_alloc (struct qed_hwfn*) ; 
 int qed_int_sp_sb_alloc (struct qed_hwfn*,struct qed_ptt*) ; 

int qed_int_alloc(struct qed_hwfn *p_hwfn, struct qed_ptt *p_ptt)
{
	int rc = 0;

	rc = qed_int_sp_dpc_alloc(p_hwfn);
	if (rc)
		return rc;

	rc = qed_int_sp_sb_alloc(p_hwfn, p_ptt);
	if (rc)
		return rc;

	rc = qed_int_sb_attn_alloc(p_hwfn, p_ptt);

	return rc;
}
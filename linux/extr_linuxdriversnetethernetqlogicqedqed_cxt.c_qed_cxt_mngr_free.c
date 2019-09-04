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
struct qed_hwfn {int /*<<< orphan*/ * p_cxt_mngr; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qed_cid_map_free (struct qed_hwfn*) ; 
 int /*<<< orphan*/  qed_cxt_src_t2_free (struct qed_hwfn*) ; 
 int /*<<< orphan*/  qed_ilt_shadow_free (struct qed_hwfn*) ; 

void qed_cxt_mngr_free(struct qed_hwfn *p_hwfn)
{
	if (!p_hwfn->p_cxt_mngr)
		return;

	qed_cid_map_free(p_hwfn);
	qed_cxt_src_t2_free(p_hwfn);
	qed_ilt_shadow_free(p_hwfn);
	kfree(p_hwfn->p_cxt_mngr);

	p_hwfn->p_cxt_mngr = NULL;
}
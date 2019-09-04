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
 int qed_cid_map_alloc (struct qed_hwfn*) ; 
 int /*<<< orphan*/  qed_cxt_mngr_free (struct qed_hwfn*) ; 
 int qed_cxt_src_t2_alloc (struct qed_hwfn*) ; 
 int qed_ilt_shadow_alloc (struct qed_hwfn*) ; 

int qed_cxt_tables_alloc(struct qed_hwfn *p_hwfn)
{
	int rc;

	/* Allocate the ILT shadow table */
	rc = qed_ilt_shadow_alloc(p_hwfn);
	if (rc)
		goto tables_alloc_fail;

	/* Allocate the T2  table */
	rc = qed_cxt_src_t2_alloc(p_hwfn);
	if (rc)
		goto tables_alloc_fail;

	/* Allocate and initialize the acquired cids bitmaps */
	rc = qed_cid_map_alloc(p_hwfn);
	if (rc)
		goto tables_alloc_fail;

	return 0;

tables_alloc_fail:
	qed_cxt_mngr_free(p_hwfn);
	return rc;
}
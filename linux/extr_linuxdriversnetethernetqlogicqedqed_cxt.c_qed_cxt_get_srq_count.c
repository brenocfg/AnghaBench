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
struct qed_hwfn {struct qed_cxt_mngr* p_cxt_mngr; } ;
struct qed_cxt_mngr {int /*<<< orphan*/  srq_count; } ;

/* Variables and functions */

u32 qed_cxt_get_srq_count(struct qed_hwfn *p_hwfn)
{
	struct qed_cxt_mngr *p_mgr = p_hwfn->p_cxt_mngr;

	return p_mgr->srq_count;
}
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
typedef  size_t u32 ;
struct qed_tid_seg {scalar_t__ count; } ;
struct qed_hwfn {struct qed_cxt_mngr* p_cxt_mngr; } ;
struct qed_cxt_mngr {TYPE_1__* conn_cfg; } ;
struct TYPE_2__ {struct qed_tid_seg* tid_seg; } ;

/* Variables and functions */
 size_t MAX_CONN_TYPES ; 

__attribute__((used)) static struct qed_tid_seg *qed_cxt_tid_seg_info(struct qed_hwfn *p_hwfn,
						u32 seg)
{
	struct qed_cxt_mngr *p_cfg = p_hwfn->p_cxt_mngr;
	u32 i;

	/* Find the protocol with tid count > 0 for this segment.
	 * Note: there can only be one and this is already validated.
	 */
	for (i = 0; i < MAX_CONN_TYPES; i++)
		if (p_cfg->conn_cfg[i].tid_seg[seg].count)
			return &p_cfg->conn_cfg[i].tid_seg[seg];
	return NULL;
}
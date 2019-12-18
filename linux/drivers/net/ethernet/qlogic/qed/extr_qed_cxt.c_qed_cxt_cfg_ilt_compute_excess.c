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
typedef  int u32 ;
struct qed_tid_seg {scalar_t__ count; size_t type; } ;
struct TYPE_2__ {int /*<<< orphan*/  val; } ;
struct qed_ilt_client_cfg {TYPE_1__ p_size; } ;
struct qed_hwfn {struct qed_cxt_mngr* p_cxt_mngr; } ;
struct qed_cxt_mngr {int* task_type_size; struct qed_ilt_client_cfg* clients; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_NOTICE (struct qed_hwfn*,char*) ; 
 size_t ILT_CLI_CDUT ; 
 int ILT_PAGE_IN_BYTES (int /*<<< orphan*/ ) ; 
 int NUM_TASK_PF_SEGMENTS ; 
 int /*<<< orphan*/  QED_ILT ; 
 int /*<<< orphan*/  QED_IS_RDMA_PERSONALITY (struct qed_hwfn*) ; 
 int RESC_NUM (struct qed_hwfn*,int /*<<< orphan*/ ) ; 
 struct qed_tid_seg* qed_cxt_tid_seg_info (struct qed_hwfn*,int) ; 

u32 qed_cxt_cfg_ilt_compute_excess(struct qed_hwfn *p_hwfn, u32 used_lines)
{
	struct qed_ilt_client_cfg *p_cli;
	u32 excess_lines, available_lines;
	struct qed_cxt_mngr *p_mngr;
	u32 ilt_page_size, elem_size;
	struct qed_tid_seg *p_seg;
	int i;

	available_lines = RESC_NUM(p_hwfn, QED_ILT);
	excess_lines = used_lines - available_lines;

	if (!excess_lines)
		return 0;

	if (!QED_IS_RDMA_PERSONALITY(p_hwfn))
		return 0;

	p_mngr = p_hwfn->p_cxt_mngr;
	p_cli = &p_mngr->clients[ILT_CLI_CDUT];
	ilt_page_size = ILT_PAGE_IN_BYTES(p_cli->p_size.val);

	for (i = 0; i < NUM_TASK_PF_SEGMENTS; i++) {
		p_seg = qed_cxt_tid_seg_info(p_hwfn, i);
		if (!p_seg || p_seg->count == 0)
			continue;

		elem_size = p_mngr->task_type_size[p_seg->type];
		if (!elem_size)
			continue;

		return (ilt_page_size / elem_size) * excess_lines;
	}

	DP_NOTICE(p_hwfn, "failed computing excess ILT lines\n");
	return 0;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct qed_tid_seg {int type; } ;
struct TYPE_8__ {int val; } ;
struct TYPE_6__ {int /*<<< orphan*/  val; } ;
struct qed_ilt_client_cfg {TYPE_4__ first; TYPE_3__* pf_blks; TYPE_2__ p_size; } ;
struct qed_hwfn {TYPE_1__* p_cxt_mngr; } ;
struct TYPE_7__ {int start_line; } ;
struct TYPE_5__ {struct qed_ilt_client_cfg* clients; } ;

/* Variables and functions */
 size_t CDUT_FL_SEG_BLK (int,int /*<<< orphan*/ ) ; 
 int CDUT_SEG_ALIGNMET_IN_BYTES ; 
 size_t CDUT_SEG_BLK (int) ; 
#define  CDU_REG_PF_FL_SEG0_TYPE_OFFSET_RT_OFFSET 135 
#define  CDU_REG_PF_FL_SEG1_TYPE_OFFSET_RT_OFFSET 134 
#define  CDU_REG_PF_FL_SEG2_TYPE_OFFSET_RT_OFFSET 133 
#define  CDU_REG_PF_FL_SEG3_TYPE_OFFSET_RT_OFFSET 132 
#define  CDU_REG_PF_SEG0_TYPE_OFFSET_RT_OFFSET 131 
#define  CDU_REG_PF_SEG1_TYPE_OFFSET_RT_OFFSET 130 
#define  CDU_REG_PF_SEG2_TYPE_OFFSET_RT_OFFSET 129 
#define  CDU_REG_PF_SEG3_TYPE_OFFSET_RT_OFFSET 128 
 int /*<<< orphan*/  CDU_SEG_REG_OFFSET ; 
 int /*<<< orphan*/  CDU_SEG_REG_TYPE ; 
 size_t ILT_CLI_CDUT ; 
 int ILT_PAGE_IN_BYTES (int /*<<< orphan*/ ) ; 
 int NUM_TASK_PF_SEGMENTS ; 
 int /*<<< orphan*/  PF ; 
 int /*<<< orphan*/  SET_FIELD (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  STORE_RT_REG (struct qed_hwfn*,int const,int) ; 
 struct qed_tid_seg* qed_cxt_tid_seg_info (struct qed_hwfn*,int) ; 

__attribute__((used)) static void qed_cdu_init_pf(struct qed_hwfn *p_hwfn)
{
	struct qed_ilt_client_cfg *p_cli;
	struct qed_tid_seg *p_seg;
	u32 cdu_seg_params, offset;
	int i;

	static const u32 rt_type_offset_arr[] = {
		CDU_REG_PF_SEG0_TYPE_OFFSET_RT_OFFSET,
		CDU_REG_PF_SEG1_TYPE_OFFSET_RT_OFFSET,
		CDU_REG_PF_SEG2_TYPE_OFFSET_RT_OFFSET,
		CDU_REG_PF_SEG3_TYPE_OFFSET_RT_OFFSET
	};

	static const u32 rt_type_offset_fl_arr[] = {
		CDU_REG_PF_FL_SEG0_TYPE_OFFSET_RT_OFFSET,
		CDU_REG_PF_FL_SEG1_TYPE_OFFSET_RT_OFFSET,
		CDU_REG_PF_FL_SEG2_TYPE_OFFSET_RT_OFFSET,
		CDU_REG_PF_FL_SEG3_TYPE_OFFSET_RT_OFFSET
	};

	p_cli = &p_hwfn->p_cxt_mngr->clients[ILT_CLI_CDUT];

	/* There are initializations only for CDUT during pf Phase */
	for (i = 0; i < NUM_TASK_PF_SEGMENTS; i++) {
		/* Segment 0 */
		p_seg = qed_cxt_tid_seg_info(p_hwfn, i);
		if (!p_seg)
			continue;

		/* Note: start_line is already adjusted for the CDU
		 * segment register granularity, so we just need to
		 * divide. Adjustment is implicit as we assume ILT
		 * Page size is larger than 32K!
		 */
		offset = (ILT_PAGE_IN_BYTES(p_cli->p_size.val) *
			  (p_cli->pf_blks[CDUT_SEG_BLK(i)].start_line -
			   p_cli->first.val)) / CDUT_SEG_ALIGNMET_IN_BYTES;

		cdu_seg_params = 0;
		SET_FIELD(cdu_seg_params, CDU_SEG_REG_TYPE, p_seg->type);
		SET_FIELD(cdu_seg_params, CDU_SEG_REG_OFFSET, offset);
		STORE_RT_REG(p_hwfn, rt_type_offset_arr[i], cdu_seg_params);

		offset = (ILT_PAGE_IN_BYTES(p_cli->p_size.val) *
			  (p_cli->pf_blks[CDUT_FL_SEG_BLK(i, PF)].start_line -
			   p_cli->first.val)) / CDUT_SEG_ALIGNMET_IN_BYTES;

		cdu_seg_params = 0;
		SET_FIELD(cdu_seg_params, CDU_SEG_REG_TYPE, p_seg->type);
		SET_FIELD(cdu_seg_params, CDU_SEG_REG_OFFSET, offset);
		STORE_RT_REG(p_hwfn, rt_type_offset_fl_arr[i], cdu_seg_params);
	}
}
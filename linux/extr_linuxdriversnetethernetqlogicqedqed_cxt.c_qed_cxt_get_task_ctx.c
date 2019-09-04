#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  size_t u32 ;
struct qed_tid_seg {size_t type; int /*<<< orphan*/  has_fl_mem; } ;
struct qed_ilt_client_cfg {struct qed_ilt_cli_blk* pf_blks; int /*<<< orphan*/  active; } ;
struct qed_ilt_cli_blk {size_t real_size_in_page; size_t start_line; int /*<<< orphan*/  total_size; } ;
struct TYPE_4__ {int personality; } ;
struct qed_hwfn {TYPE_1__ hw_info; struct qed_cxt_mngr* p_cxt_mngr; } ;
struct qed_cxt_mngr {size_t* task_type_size; size_t pf_start_line; TYPE_3__* ilt_shadow; TYPE_2__* conn_cfg; struct qed_ilt_client_cfg* clients; } ;
struct TYPE_6__ {scalar_t__ p_virt; } ;
struct TYPE_5__ {struct qed_tid_seg* tid_seg; } ;

/* Variables and functions */
 size_t CDUT_FL_SEG_BLK (size_t,int /*<<< orphan*/ ) ; 
 size_t CDUT_SEG_BLK (size_t) ; 
 size_t DIV_ROUND_UP (int /*<<< orphan*/ ,size_t) ; 
 int EINVAL ; 
 size_t ILT_CLI_CDUT ; 
 int /*<<< orphan*/  PF ; 
 size_t PROTOCOLID_FCOE ; 
 size_t PROTOCOLID_ISCSI ; 
 scalar_t__ QED_CTX_FL_MEM ; 
 scalar_t__ QED_CTX_WORKING_MEM ; 
 size_t QED_CXT_FCOE_TID_SEG ; 
 size_t QED_CXT_ISCSI_TID_SEG ; 
#define  QED_PCI_FCOE 129 
#define  QED_PCI_ISCSI 128 

int qed_cxt_get_task_ctx(struct qed_hwfn *p_hwfn,
			 u32 tid, u8 ctx_type, void **pp_task_ctx)
{
	struct qed_cxt_mngr *p_mngr = p_hwfn->p_cxt_mngr;
	struct qed_ilt_client_cfg *p_cli;
	struct qed_tid_seg *p_seg_info;
	struct qed_ilt_cli_blk *p_seg;
	u32 num_tids_per_block;
	u32 tid_size, ilt_idx;
	u32 total_lines;
	u32 proto, seg;

	/* Verify the personality */
	switch (p_hwfn->hw_info.personality) {
	case QED_PCI_FCOE:
		proto = PROTOCOLID_FCOE;
		seg = QED_CXT_FCOE_TID_SEG;
		break;
	case QED_PCI_ISCSI:
		proto = PROTOCOLID_ISCSI;
		seg = QED_CXT_ISCSI_TID_SEG;
		break;
	default:
		return -EINVAL;
	}

	p_cli = &p_mngr->clients[ILT_CLI_CDUT];
	if (!p_cli->active)
		return -EINVAL;

	p_seg_info = &p_mngr->conn_cfg[proto].tid_seg[seg];

	if (ctx_type == QED_CTX_WORKING_MEM) {
		p_seg = &p_cli->pf_blks[CDUT_SEG_BLK(seg)];
	} else if (ctx_type == QED_CTX_FL_MEM) {
		if (!p_seg_info->has_fl_mem)
			return -EINVAL;
		p_seg = &p_cli->pf_blks[CDUT_FL_SEG_BLK(seg, PF)];
	} else {
		return -EINVAL;
	}
	total_lines = DIV_ROUND_UP(p_seg->total_size, p_seg->real_size_in_page);
	tid_size = p_mngr->task_type_size[p_seg_info->type];
	num_tids_per_block = p_seg->real_size_in_page / tid_size;

	if (total_lines < tid / num_tids_per_block)
		return -EINVAL;

	ilt_idx = tid / num_tids_per_block + p_seg->start_line -
		  p_mngr->pf_start_line;
	*pp_task_ctx = (u8 *)p_mngr->ilt_shadow[ilt_idx].p_virt +
		       (tid % num_tids_per_block) * tid_size;

	return 0;
}
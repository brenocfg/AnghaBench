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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct qed_vf_info {int abs_vf_id; int* igu_sbs; scalar_t__ num_sbs; } ;
struct qed_ptt {int dummy; } ;
struct qed_igu_block {int igu_sb_id; int /*<<< orphan*/  status; } ;
struct TYPE_6__ {TYPE_2__* p_igu_info; } ;
struct qed_hwfn {int /*<<< orphan*/  rel_pf_id; TYPE_3__ hw_info; } ;
struct cau_sb_entry {int dummy; } ;
struct TYPE_4__ {int free_cnt_iov; } ;
struct TYPE_5__ {TYPE_1__ usage; } ;

/* Variables and functions */
 scalar_t__ CAU_REG_SB_VAR_MEMORY ; 
 int /*<<< orphan*/  IGU_MAPPING_LINE_FUNCTION_NUMBER ; 
 int /*<<< orphan*/  IGU_MAPPING_LINE_PF_VALID ; 
 int /*<<< orphan*/  IGU_MAPPING_LINE_VALID ; 
 int /*<<< orphan*/  IGU_MAPPING_LINE_VECTOR_NUMBER ; 
 scalar_t__ IGU_REG_MAPPING_MEMORY ; 
 int /*<<< orphan*/  QED_IGU_STATUS_FREE ; 
 int /*<<< orphan*/  SET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qed_dmae_host2grc (struct qed_hwfn*,struct qed_ptt*,int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ *) ; 
 struct qed_igu_block* qed_get_igu_free_sb (struct qed_hwfn*,int) ; 
 int /*<<< orphan*/  qed_init_cau_sb_entry (struct qed_hwfn*,struct cau_sb_entry*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  qed_wr (struct qed_hwfn*,struct qed_ptt*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u8 qed_iov_alloc_vf_igu_sbs(struct qed_hwfn *p_hwfn,
				   struct qed_ptt *p_ptt,
				   struct qed_vf_info *vf, u16 num_rx_queues)
{
	struct qed_igu_block *p_block;
	struct cau_sb_entry sb_entry;
	int qid = 0;
	u32 val = 0;

	if (num_rx_queues > p_hwfn->hw_info.p_igu_info->usage.free_cnt_iov)
		num_rx_queues = p_hwfn->hw_info.p_igu_info->usage.free_cnt_iov;
	p_hwfn->hw_info.p_igu_info->usage.free_cnt_iov -= num_rx_queues;

	SET_FIELD(val, IGU_MAPPING_LINE_FUNCTION_NUMBER, vf->abs_vf_id);
	SET_FIELD(val, IGU_MAPPING_LINE_VALID, 1);
	SET_FIELD(val, IGU_MAPPING_LINE_PF_VALID, 0);

	for (qid = 0; qid < num_rx_queues; qid++) {
		p_block = qed_get_igu_free_sb(p_hwfn, false);
		vf->igu_sbs[qid] = p_block->igu_sb_id;
		p_block->status &= ~QED_IGU_STATUS_FREE;
		SET_FIELD(val, IGU_MAPPING_LINE_VECTOR_NUMBER, qid);

		qed_wr(p_hwfn, p_ptt,
		       IGU_REG_MAPPING_MEMORY +
		       sizeof(u32) * p_block->igu_sb_id, val);

		/* Configure igu sb in CAU which were marked valid */
		qed_init_cau_sb_entry(p_hwfn, &sb_entry,
				      p_hwfn->rel_pf_id, vf->abs_vf_id, 1);

		qed_dmae_host2grc(p_hwfn, p_ptt,
				  (u64)(uintptr_t)&sb_entry,
				  CAU_REG_SB_VAR_MEMORY +
				  p_block->igu_sb_id * sizeof(u64), 2, NULL);
	}

	vf->num_sbs = (u8) num_rx_queues;

	return vf->num_sbs;
}
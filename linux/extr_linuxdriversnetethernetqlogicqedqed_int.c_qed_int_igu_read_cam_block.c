#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct qed_ptt {int dummy; } ;
struct qed_igu_block {int igu_sb_id; void* vector_number; void* is_pf; void* function_id; } ;
struct TYPE_4__ {TYPE_1__* p_igu_info; } ;
struct qed_hwfn {TYPE_2__ hw_info; } ;
struct TYPE_3__ {struct qed_igu_block* entry; } ;

/* Variables and functions */
 void* GET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IGU_MAPPING_LINE_FUNCTION_NUMBER ; 
 int /*<<< orphan*/  IGU_MAPPING_LINE_PF_VALID ; 
 int /*<<< orphan*/  IGU_MAPPING_LINE_VECTOR_NUMBER ; 
 scalar_t__ IGU_REG_MAPPING_MEMORY ; 
 int /*<<< orphan*/  qed_rd (struct qed_hwfn*,struct qed_ptt*,scalar_t__) ; 

__attribute__((used)) static void qed_int_igu_read_cam_block(struct qed_hwfn *p_hwfn,
				       struct qed_ptt *p_ptt, u16 igu_sb_id)
{
	u32 val = qed_rd(p_hwfn, p_ptt,
			 IGU_REG_MAPPING_MEMORY + sizeof(u32) * igu_sb_id);
	struct qed_igu_block *p_block;

	p_block = &p_hwfn->hw_info.p_igu_info->entry[igu_sb_id];

	/* Fill the block information */
	p_block->function_id = GET_FIELD(val, IGU_MAPPING_LINE_FUNCTION_NUMBER);
	p_block->is_pf = GET_FIELD(val, IGU_MAPPING_LINE_PF_VALID);
	p_block->vector_number = GET_FIELD(val, IGU_MAPPING_LINE_VECTOR_NUMBER);
	p_block->igu_sb_id = igu_sb_id;
}
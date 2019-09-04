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
typedef  size_t u8 ;
struct qed_hwfn {int dummy; } ;
struct block_defs {scalar_t__ storm_id; scalar_t__ associated_to_storm; } ;
struct big_ram_defs {size_t mem_group_id; size_t ram_mem_group_id; int /*<<< orphan*/  grc_param; } ;
typedef  enum dbg_storms { ____Placeholder_dbg_storms } dbg_storms ;
typedef  enum block_id { ____Placeholder_block_id } block_id ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_GRC_PARAM_DUMP_CAU ; 
 int /*<<< orphan*/  DBG_GRC_PARAM_DUMP_CFC ; 
 int /*<<< orphan*/  DBG_GRC_PARAM_DUMP_CM ; 
 int /*<<< orphan*/  DBG_GRC_PARAM_DUMP_CM_CTX ; 
 int /*<<< orphan*/  DBG_GRC_PARAM_DUMP_DIF ; 
 int /*<<< orphan*/  DBG_GRC_PARAM_DUMP_DMAE ; 
 int /*<<< orphan*/  DBG_GRC_PARAM_DUMP_IGU ; 
 int /*<<< orphan*/  DBG_GRC_PARAM_DUMP_IOR ; 
 int /*<<< orphan*/  DBG_GRC_PARAM_DUMP_MULD ; 
 int /*<<< orphan*/  DBG_GRC_PARAM_DUMP_PBUF ; 
 int /*<<< orphan*/  DBG_GRC_PARAM_DUMP_PRS ; 
 int /*<<< orphan*/  DBG_GRC_PARAM_DUMP_PXP ; 
 int /*<<< orphan*/  DBG_GRC_PARAM_DUMP_QM ; 
 int /*<<< orphan*/  DBG_GRC_PARAM_DUMP_RAM ; 
 int /*<<< orphan*/  DBG_GRC_PARAM_DUMP_SDM ; 
 int /*<<< orphan*/  DBG_GRC_PARAM_DUMP_TM ; 
#define  MEM_GROUP_CAU_MEM 149 
#define  MEM_GROUP_CAU_PI 148 
#define  MEM_GROUP_CAU_SB 147 
#define  MEM_GROUP_CFC_MEM 146 
#define  MEM_GROUP_CM_MEM 145 
#define  MEM_GROUP_CONN_CFC_MEM 144 
#define  MEM_GROUP_DMAE_MEM 143 
#define  MEM_GROUP_IGU_MEM 142 
#define  MEM_GROUP_IGU_MSIX 141 
#define  MEM_GROUP_IOR 140 
#define  MEM_GROUP_MULD_MEM 139 
#define  MEM_GROUP_PBUF 138 
#define  MEM_GROUP_PRS_MEM 137 
#define  MEM_GROUP_PXP_ILT 136 
#define  MEM_GROUP_PXP_MEM 135 
#define  MEM_GROUP_QM_MEM 134 
#define  MEM_GROUP_RAM 133 
#define  MEM_GROUP_RDIF_CTX 132 
#define  MEM_GROUP_SDM_MEM 131 
#define  MEM_GROUP_TASK_CFC_MEM 130 
#define  MEM_GROUP_TDIF_CTX 129 
#define  MEM_GROUP_TM_MEM 128 
 size_t NUM_BIG_RAM_TYPES ; 
 int qed_grc_is_included (struct qed_hwfn*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qed_grc_is_storm_included (struct qed_hwfn*,int) ; 
 struct big_ram_defs* s_big_ram_defs ; 
 struct block_defs** s_block_defs ; 

__attribute__((used)) static bool qed_grc_is_mem_included(struct qed_hwfn *p_hwfn,
				    enum block_id block_id, u8 mem_group_id)
{
	struct block_defs *block = s_block_defs[block_id];
	u8 i;

	/* Check Storm match */
	if (block->associated_to_storm &&
	    !qed_grc_is_storm_included(p_hwfn,
				       (enum dbg_storms)block->storm_id))
		return false;

	for (i = 0; i < NUM_BIG_RAM_TYPES; i++) {
		struct big_ram_defs *big_ram = &s_big_ram_defs[i];

		if (mem_group_id == big_ram->mem_group_id ||
		    mem_group_id == big_ram->ram_mem_group_id)
			return qed_grc_is_included(p_hwfn, big_ram->grc_param);
	}

	switch (mem_group_id) {
	case MEM_GROUP_PXP_ILT:
	case MEM_GROUP_PXP_MEM:
		return qed_grc_is_included(p_hwfn, DBG_GRC_PARAM_DUMP_PXP);
	case MEM_GROUP_RAM:
		return qed_grc_is_included(p_hwfn, DBG_GRC_PARAM_DUMP_RAM);
	case MEM_GROUP_PBUF:
		return qed_grc_is_included(p_hwfn, DBG_GRC_PARAM_DUMP_PBUF);
	case MEM_GROUP_CAU_MEM:
	case MEM_GROUP_CAU_SB:
	case MEM_GROUP_CAU_PI:
		return qed_grc_is_included(p_hwfn, DBG_GRC_PARAM_DUMP_CAU);
	case MEM_GROUP_QM_MEM:
		return qed_grc_is_included(p_hwfn, DBG_GRC_PARAM_DUMP_QM);
	case MEM_GROUP_CFC_MEM:
	case MEM_GROUP_CONN_CFC_MEM:
	case MEM_GROUP_TASK_CFC_MEM:
		return qed_grc_is_included(p_hwfn, DBG_GRC_PARAM_DUMP_CFC) ||
		       qed_grc_is_included(p_hwfn, DBG_GRC_PARAM_DUMP_CM_CTX);
	case MEM_GROUP_IGU_MEM:
	case MEM_GROUP_IGU_MSIX:
		return qed_grc_is_included(p_hwfn, DBG_GRC_PARAM_DUMP_IGU);
	case MEM_GROUP_MULD_MEM:
		return qed_grc_is_included(p_hwfn, DBG_GRC_PARAM_DUMP_MULD);
	case MEM_GROUP_PRS_MEM:
		return qed_grc_is_included(p_hwfn, DBG_GRC_PARAM_DUMP_PRS);
	case MEM_GROUP_DMAE_MEM:
		return qed_grc_is_included(p_hwfn, DBG_GRC_PARAM_DUMP_DMAE);
	case MEM_GROUP_TM_MEM:
		return qed_grc_is_included(p_hwfn, DBG_GRC_PARAM_DUMP_TM);
	case MEM_GROUP_SDM_MEM:
		return qed_grc_is_included(p_hwfn, DBG_GRC_PARAM_DUMP_SDM);
	case MEM_GROUP_TDIF_CTX:
	case MEM_GROUP_RDIF_CTX:
		return qed_grc_is_included(p_hwfn, DBG_GRC_PARAM_DUMP_DIF);
	case MEM_GROUP_CM_MEM:
		return qed_grc_is_included(p_hwfn, DBG_GRC_PARAM_DUMP_CM);
	case MEM_GROUP_IOR:
		return qed_grc_is_included(p_hwfn, DBG_GRC_PARAM_DUMP_IOR);
	default:
		return true;
	}
}
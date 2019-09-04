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
struct hubp {int dummy; } ;
struct dcn10_hubp {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  pte_row_height_linear; int /*<<< orphan*/  swath_height; int /*<<< orphan*/  mpte_group_size; int /*<<< orphan*/  dpte_group_size; int /*<<< orphan*/  min_meta_chunk_size; int /*<<< orphan*/  meta_chunk_size; int /*<<< orphan*/  min_chunk_size; int /*<<< orphan*/  chunk_size; } ;
struct TYPE_3__ {int /*<<< orphan*/  pte_row_height_linear; int /*<<< orphan*/  swath_height; int /*<<< orphan*/  mpte_group_size; int /*<<< orphan*/  dpte_group_size; int /*<<< orphan*/  min_meta_chunk_size; int /*<<< orphan*/  meta_chunk_size; int /*<<< orphan*/  min_chunk_size; int /*<<< orphan*/  chunk_size; } ;
struct _vcs_dpi_display_rq_regs_st {TYPE_2__ rq_regs_c; TYPE_1__ rq_regs_l; int /*<<< orphan*/  crq_expansion_mode; int /*<<< orphan*/  mrq_expansion_mode; int /*<<< orphan*/  prq_expansion_mode; int /*<<< orphan*/  drq_expansion_mode; int /*<<< orphan*/  plane1_base_address; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHUNK_SIZE ; 
 int /*<<< orphan*/  CHUNK_SIZE_C ; 
 int /*<<< orphan*/  CRQ_EXPANSION_MODE ; 
 int /*<<< orphan*/  DCHUBP_REQ_SIZE_CONFIG ; 
 int /*<<< orphan*/  DCHUBP_REQ_SIZE_CONFIG_C ; 
 int /*<<< orphan*/  DCN_EXPANSION_MODE ; 
 int /*<<< orphan*/  DET_BUF_PLANE1_BASE_ADDRESS ; 
 int /*<<< orphan*/  DPTE_GROUP_SIZE ; 
 int /*<<< orphan*/  DPTE_GROUP_SIZE_C ; 
 int /*<<< orphan*/  DRQ_EXPANSION_MODE ; 
 int /*<<< orphan*/  HUBPRET_CONTROL ; 
 int /*<<< orphan*/  META_CHUNK_SIZE ; 
 int /*<<< orphan*/  META_CHUNK_SIZE_C ; 
 int /*<<< orphan*/  MIN_CHUNK_SIZE ; 
 int /*<<< orphan*/  MIN_CHUNK_SIZE_C ; 
 int /*<<< orphan*/  MIN_META_CHUNK_SIZE ; 
 int /*<<< orphan*/  MIN_META_CHUNK_SIZE_C ; 
 int /*<<< orphan*/  MPTE_GROUP_SIZE ; 
 int /*<<< orphan*/  MPTE_GROUP_SIZE_C ; 
 int /*<<< orphan*/  MRQ_EXPANSION_MODE ; 
 int /*<<< orphan*/  PRQ_EXPANSION_MODE ; 
 int /*<<< orphan*/  PTE_ROW_HEIGHT_LINEAR ; 
 int /*<<< orphan*/  PTE_ROW_HEIGHT_LINEAR_C ; 
 int /*<<< orphan*/  REG_SET_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_SET_8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_UPDATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SWATH_HEIGHT ; 
 int /*<<< orphan*/  SWATH_HEIGHT_C ; 
 struct dcn10_hubp* TO_DCN10_HUBP (struct hubp*) ; 

void hubp1_program_requestor(
		struct hubp *hubp,
		struct _vcs_dpi_display_rq_regs_st *rq_regs)
{
	struct dcn10_hubp *hubp1 = TO_DCN10_HUBP(hubp);

	REG_UPDATE(HUBPRET_CONTROL,
			DET_BUF_PLANE1_BASE_ADDRESS, rq_regs->plane1_base_address);
	REG_SET_4(DCN_EXPANSION_MODE, 0,
			DRQ_EXPANSION_MODE, rq_regs->drq_expansion_mode,
			PRQ_EXPANSION_MODE, rq_regs->prq_expansion_mode,
			MRQ_EXPANSION_MODE, rq_regs->mrq_expansion_mode,
			CRQ_EXPANSION_MODE, rq_regs->crq_expansion_mode);
	REG_SET_8(DCHUBP_REQ_SIZE_CONFIG, 0,
		CHUNK_SIZE, rq_regs->rq_regs_l.chunk_size,
		MIN_CHUNK_SIZE, rq_regs->rq_regs_l.min_chunk_size,
		META_CHUNK_SIZE, rq_regs->rq_regs_l.meta_chunk_size,
		MIN_META_CHUNK_SIZE, rq_regs->rq_regs_l.min_meta_chunk_size,
		DPTE_GROUP_SIZE, rq_regs->rq_regs_l.dpte_group_size,
		MPTE_GROUP_SIZE, rq_regs->rq_regs_l.mpte_group_size,
		SWATH_HEIGHT, rq_regs->rq_regs_l.swath_height,
		PTE_ROW_HEIGHT_LINEAR, rq_regs->rq_regs_l.pte_row_height_linear);
	REG_SET_8(DCHUBP_REQ_SIZE_CONFIG_C, 0,
		CHUNK_SIZE_C, rq_regs->rq_regs_c.chunk_size,
		MIN_CHUNK_SIZE_C, rq_regs->rq_regs_c.min_chunk_size,
		META_CHUNK_SIZE_C, rq_regs->rq_regs_c.meta_chunk_size,
		MIN_META_CHUNK_SIZE_C, rq_regs->rq_regs_c.min_meta_chunk_size,
		DPTE_GROUP_SIZE_C, rq_regs->rq_regs_c.dpte_group_size,
		MPTE_GROUP_SIZE_C, rq_regs->rq_regs_c.mpte_group_size,
		SWATH_HEIGHT_C, rq_regs->rq_regs_c.swath_height,
		PTE_ROW_HEIGHT_LINEAR_C, rq_regs->rq_regs_c.pte_row_height_linear);
}
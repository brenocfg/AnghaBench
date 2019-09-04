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
typedef  size_t u8 ;
typedef  size_t u32 ;
typedef  scalar_t__ u16 ;
struct storm_defs {size_t block_id; scalar_t__ sem_fast_mem_addr; } ;
struct qed_ptt {int dummy; } ;
struct dbg_tools_data {scalar_t__* block_in_reset; } ;
struct qed_hwfn {struct dbg_tools_data dbg_info; } ;
struct TYPE_2__ {int /*<<< orphan*/  data; } ;
struct dbg_attn_reg {size_t mask_address; int /*<<< orphan*/  data; TYPE_1__ mode; } ;
typedef  enum block_id { ____Placeholder_block_id } block_id ;

/* Variables and functions */
 int /*<<< orphan*/  ATTN_TYPE_PARITY ; 
 size_t BYTES_TO_DWORDS (scalar_t__) ; 
 int /*<<< orphan*/  DBG_ATTN_REG_STS_ADDRESS ; 
 int /*<<< orphan*/  DBG_MODE_HDR_EVAL_MODE ; 
 int /*<<< orphan*/  DBG_MODE_HDR_MODES_BUF_OFFSET ; 
 scalar_t__ GET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t MAX_BLOCK_ID ; 
 size_t MAX_DBG_STORMS ; 
 scalar_t__ SEM_FAST_REG_STALLED ; 
 int /*<<< orphan*/  SPLIT_TYPE_NONE ; 
 struct dbg_attn_reg* qed_get_block_attn_regs (int,int /*<<< orphan*/ ,size_t*) ; 
 size_t qed_grc_dump_reg_entry (struct qed_hwfn*,struct qed_ptt*,size_t*,int,size_t,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t qed_grc_dump_regs_hdr (size_t*,int,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qed_is_mode_match (struct qed_hwfn*,scalar_t__*) ; 
 struct storm_defs* s_storm_defs ; 

__attribute__((used)) static u32 qed_grc_dump_modified_regs(struct qed_hwfn *p_hwfn,
				      struct qed_ptt *p_ptt,
				      u32 *dump_buf, bool dump)
{
	struct dbg_tools_data *dev_data = &p_hwfn->dbg_info;
	u32 block_id, offset = 0, num_reg_entries = 0;
	const struct dbg_attn_reg *attn_reg_arr;
	u8 storm_id, reg_idx, num_attn_regs;

	/* Calculate header size */
	offset += qed_grc_dump_regs_hdr(dump_buf,
					false, 0, SPLIT_TYPE_NONE,
					0, NULL, NULL);

	/* Write parity registers */
	for (block_id = 0; block_id < MAX_BLOCK_ID; block_id++) {
		if (dev_data->block_in_reset[block_id] && dump)
			continue;

		attn_reg_arr = qed_get_block_attn_regs((enum block_id)block_id,
						       ATTN_TYPE_PARITY,
						       &num_attn_regs);

		for (reg_idx = 0; reg_idx < num_attn_regs; reg_idx++) {
			const struct dbg_attn_reg *reg_data =
				&attn_reg_arr[reg_idx];
			u16 modes_buf_offset;
			bool eval_mode;
			u32 addr;

			/* Check mode */
			eval_mode = GET_FIELD(reg_data->mode.data,
					      DBG_MODE_HDR_EVAL_MODE) > 0;
			modes_buf_offset =
				GET_FIELD(reg_data->mode.data,
					  DBG_MODE_HDR_MODES_BUF_OFFSET);
			if (eval_mode &&
			    !qed_is_mode_match(p_hwfn, &modes_buf_offset))
				continue;

			/* Mode match: read & dump registers */
			addr = reg_data->mask_address;
			offset += qed_grc_dump_reg_entry(p_hwfn,
							 p_ptt,
							 dump_buf + offset,
							 dump,
							 addr,
							 1, false,
							 SPLIT_TYPE_NONE, 0);
			addr = GET_FIELD(reg_data->data,
					 DBG_ATTN_REG_STS_ADDRESS);
			offset += qed_grc_dump_reg_entry(p_hwfn,
							 p_ptt,
							 dump_buf + offset,
							 dump,
							 addr,
							 1, false,
							 SPLIT_TYPE_NONE, 0);
			num_reg_entries += 2;
		}
	}

	/* Write Storm stall status registers */
	for (storm_id = 0; storm_id < MAX_DBG_STORMS; storm_id++) {
		struct storm_defs *storm = &s_storm_defs[storm_id];
		u32 addr;

		if (dev_data->block_in_reset[storm->block_id] && dump)
			continue;

		addr =
		    BYTES_TO_DWORDS(s_storm_defs[storm_id].sem_fast_mem_addr +
				    SEM_FAST_REG_STALLED);
		offset += qed_grc_dump_reg_entry(p_hwfn,
						 p_ptt,
						 dump_buf + offset,
						 dump,
						 addr,
						 1,
						 false, SPLIT_TYPE_NONE, 0);
		num_reg_entries++;
	}

	/* Write header */
	if (dump)
		qed_grc_dump_regs_hdr(dump_buf,
				      true,
				      num_reg_entries, SPLIT_TYPE_NONE,
				      0, NULL, NULL);

	return offset;
}